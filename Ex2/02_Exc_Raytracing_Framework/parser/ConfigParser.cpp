/****************************************************************************
|*  ConfigParser.h
|*
|*  ConfigParser class. Parses the Ray Tracers Config file and generates an appropriate renderer.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

//#define READ_SUPERSAMPLER_FLAG 1
//#define READ_BUMPMAP_FLAG 1


#include <iostream>

#include <Renderer.h>
#include <utils/string_conversions.h>
#include <parser/SimpleXMLNode.h>
#include <rendererelements/shader/IShader.h>
#include <rendererelements/ISampler.h>
#include <rendererelements/shader/PhongLightingShader.h> 

#include <rendererelements/shader/DiffuseLightingShader.h>  
#include <rendererelements/shader/ConstantShader.h> 
#include <rendererelements/ScanlineSampler.h>
#include <rendererelements/ProgressiveSampler.h>

#ifdef READ_SUPERSAMPLER_FLAG
#include <rendererelements/shader/PhongBumpShader.h> 
#include <rendererelements/SuperSampler.h>
#endif


#include "ConfigParser.h"


ConfigParser::ConfigParser(void){
}


ConfigParser::~ConfigParser(void){
}


//parse a config file and generate a Renderer
Renderer* ConfigParser::parse(std::string filename){
	
	std::cout << "ConfigParser::parse config file... " << filename <<" \n";

	struct basicxmlnode * rootNode = NULL;

	//open file
	FILE * fp = fopen(filename.c_str(), "rt");
	if (!fp) {
		std::cerr << "ConfigParser - Error: Failed opening file " << filename << "\n";
		return NULL;
	}

	rootNode = readbasicxmlnode(fp);
	fclose(fp);
	if (!rootNode) {
		std::cerr << "ConfigParser - Error: Failed reading file " << filename << ". Maybe an XML syntax error?\n";
		return NULL;
	}

	//create renderer
	Renderer* renderer = new Renderer();

	//read renderer properties
	if (!addRendererProperties(rootNode, renderer)) {
		std::cerr << "ConfigParser - Error: Failed reading renderer properties in " << filename << "\n";
		deletebasicxmlnode(rootNode);
		delete(renderer);
		return NULL;
	}

	//read sampler
	struct basicxmlnode * samplerNode = getchildnodebyname(rootNode, "Sampler");
	if (!addSampler(samplerNode, renderer)) {
		std::cerr << "ConfigParser - Error: Failed reading sampler description in " << filename << "\n";
		deletebasicxmlnode(rootNode);
		delete(renderer);
		return NULL;
	}
	
	//read shader
	struct basicxmlnode * shaderNode = getchildnodebyname(rootNode, "Shader");
	if (!addShader(shaderNode, renderer)) {
		std::cerr << "ConfigParser - Error: Failed reading shader description in " << filename << "\n";
		deletebasicxmlnode(rootNode);
		delete(renderer);
		return NULL;
	}

	//free xml memory
	deletebasicxmlnode(rootNode);

	std::cout << "[done]\n\n";

	return renderer;
}

bool ConfigParser::addRendererProperties(struct basicxmlnode * rendererNode, Renderer * renderer) {

	if (!rendererNode) {
		std::cout << "ConfigParser::addRendererProperties: empty renderer node\n";
		return false;
	}

	if (std::string(rendererNode->tag) != "Renderer") {
		std::cout << "ConfigParser::addRendererProperties: config file has to have toplevel Renderer node\n";
		return false;
	}

	// read renderer properties
	unsigned int recursionDepth;

	char * attributeValue;
	if (attributeValue = getattributevaluebyname(rendererNode, "recursionDepth")) {
		if (!stringToNumber<unsigned int>(recursionDepth, attributeValue)) {
			return false;
		}	
		renderer->setRecursiondepth(recursionDepth);
	}

	return true;
}

bool  ConfigParser::addSampler(struct basicxmlnode * samplerNode, Renderer * renderer){
	if (!samplerNode) {
		std::cout << "ConfigParser::addSampler: empty sampler node\n";
		return false;
	}

	if (std::string(samplerNode->tag) != "Sampler") {
		std::cout << "ConfigParser::addSampler: wrong sampler tag name\n";
		return false;
	}

	// read sampler type
	std::string type = getattributevaluebyname(samplerNode, "type");
	if (type == "ScanlineSampler") {
		renderer->setSampler(new ScanlineSampler());
	}
#ifdef READ_SUPERSAMPLER_FLAG
	else if (type == "SuperSampler") {
		double sample_pixel=1;
		char* attributeValue;
		if (attributeValue = getattributevaluebyname(samplerNode, "mSubsamples")) {
			if (!stringToNumber<double>(sample_pixel, attributeValue)) {
				return false;
			}
		}
		bool jitter = false;
		if (attributeValue = getattributevaluebyname(samplerNode, "jitter")) {
			std::string jittervalue = getattributevaluebyname(samplerNode, "jitter");
			jitter = (jittervalue == "yes") ? true : false;
		}

		ISampler* s = new SuperSampler((int)sample_pixel, jitter);
		renderer->setSampler(s);
	}
#endif
	else if (type == "ProgressiveSampler") {
		renderer->setSampler(new ProgressiveSampler());
	}
	else {
		std::cout << "ConfigParser::addSampler: unknown sampler specified\n";
		return false;
	}

	return true;
}

bool  ConfigParser::addShader(struct basicxmlnode * shaderNode, Renderer * renderer){
	if (!shaderNode) {
		std::cout << "ConfigParser::addShader: empty shader node\n";
		return false;
	}

	if (std::string(shaderNode->tag) != "Shader") {
		std::cout << "ConfigParser::addShader: wrong shader tag name\n";
		return false;
	}

	// read shader type
	std::string type = getattributevaluebyname(shaderNode, "type");
	if (type == "ConstantShader") {
		renderer->setShader(new ConstantShader());
	}
	else if (type == "DiffuseLightingShader") {
		renderer->setShader(new DiffuseLightingShader());
	}
	else if (type == "PhongLightingShader") {
		renderer->setShader(new PhongLightingShader());
	}
#ifdef READ_BUMPMAP_FLAG
	else if (type == "PhongBumpShader") {
		renderer->setShader(new PhongBumpShader());
	}
#endif
	else {
		std::cout << "ConfigParser::addShader: unknown shader specified\n";
		return false;
	}

	return true;
}

