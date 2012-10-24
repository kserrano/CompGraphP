//=============================================================================
//                                                                            
//   Exercise code for Introduction to Computer Graphics
//   LGG - EPFL
//   Thibaut Weise, Yuliy Schwartzburg
//                                                                            
//=============================================================================
//=============================================================================
//
//   CLASS Object3D
//
//=============================================================================


#ifndef OBJECT3D_HH
#define OBJECT3D_HH


//== INCLUDES =================================================================

#include "../math/Matrix4.h"

//== CLASS DEFINITION =========================================================





/*  
	 Basic 3D Object
*/

class Object3D
{
  
public:
    //------------------------------------------------ public methods

	//! constructor which sets the object to world transformation to identity
	Object3D()
    {
		m_transformationMatrix.loadIdentity();
	}
	
	//! destructor
	virtual ~Object3D() {}
	
	//! return the transformation from object to world coordinates
	const Matrix4 & getTransformation() const
    {
        return m_transformationMatrix;
    }

	//! set the current transformation
	void setTransformation( const Matrix4 & mat )
    {
        m_transformationMatrix = mat;
    }
	
	//! return origin of object in world coordinates
	Vector3 origin() const {
		return m_transformationMatrix * Vector3(0,0,0);
	}

	//! set transformation matrix to identity
	void setIdentity() {
		m_transformationMatrix.loadIdentity();
	}
	
	//! translates the object in the world coordinate system
	void translateWorld( const Vector3 & _trans )
	{
		m_transformationMatrix = getTranslationMatrix(_trans)*m_transformationMatrix;
		// ((( Exercise 3.4 )))
	}
	
	
	//! translates the object in the object coordinate systems
	void translateObject( const Vector3 & _trans )
	{
		m_transformationMatrix = m_transformationMatrix*getTranslationMatrix(_trans);
		// ((( Exercise 3.4 )))

	}
	
	//! scales the object in the world coordinate system
	void scaleWorld( const Vector3 & _scl )
	{
        m_transformationMatrix= getScaleMatrix(_scl)*m_transformationMatrix;
		// ((( Exercise 3.4 )))
	}

	//! scales the object in the object coordinate systems
	void scaleObject( const Vector3 & _scl )
	{
        m_transformationMatrix = m_transformationMatrix*getScaleMatrix(_scl);
		// ((( Exercise 3.4 )))
	}

	//! rotates the object in the world coordinate system
	void rotateWorld( const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = getRotationMatrix(_axis,_angle)*m_transformationMatrix;
		// ((( Exercise 3.4 )))

	}

	//! rotates the object in the object coordinate system
	void rotateObject( const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = m_transformationMatrix*getRotationMatrix(_axis,_angle);
		// ((( Exercise 3.4 )))
	}


	//! rotates the object around an arbitrary axis in world coordinate system
	void rotateAroundAxisWorld( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = (getTranslationMatrix(-_pt)*getRotationMatrix(_axis,_angle)*getTranslationMatrix(_pt))*m_transformationMatrix;
		// ((( Exercise 3.4 )))
	}

	//! rotates the object around an arbitrary axis in object coordinate system
	void rotateAroundAxisObject( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        m_transformationMatrix =  m_transformationMatrix*(getTranslationMatrix(-_pt)*getRotationMatrix(_axis,_angle)*getTranslationMatrix(_pt));
		// ((( Exercise 3.4 )))
	}


	//! calculate translation matrix from vector
	static Matrix4 getTranslationMatrix(const Vector3 & _trans) {

		//Matrix4 translationMatrix;
        
		// ((( Exercise 3.4 )))
        //translationMatrix.loadIdentity();
		
		return Matrix4(
			          1, 0, 0, _trans.x,
                      0, 1, 0, _trans.y,
                      0, 0, 1, _trans.z,
                      0, 0, 0, 1
                      );;
	}
	
	//! calculate scale matrix from vector
	static Matrix4 getScaleMatrix(const Vector3 & _scale) {
		
		//Matrix4 scaleMatrix;
        
		// ((( Exercise 3.4 )))
        //scaleMatrix.loadIdentity();
		
		return Matrix4 (
					   _scale.x, 0, 0, 0,
					   0, _scale.y, 0, 0,
					   0, 0, _scale.z, 0,
					   0, 0, 0, 1
					   );;
	}
	
	//! calculate rotation matrix from rotation axis and angle in radian
	static Matrix4 getRotationMatrix(const Vector3 & axis, double angle) {
		double cosa = cos(angle);
		double sina = sin(angle);
		double ux = axis.x;
		double uy = axis.y;
		double uz = axis.z;
		//Matrix4 rotationMatrix;

		// ((( Exercise 3.4 )))
		//rotationMatrix.loadIdentity();
        
		return Matrix4 (
						 cosa + ux*ux*(1-cosa), ux*uy*(1-cosa)-uz*sina, ux*uz*(1-cosa)+uy*sina, 0,
						 uy*ux*(1-cosa)+uz*sina, cosa + uy*uy*(1-cosa), uy*uz*(1-cosa)-ux*sina, 0,
						 uz*ux*(1-cosa)-uy*sina, uz*uy*(1-cosa)+ux*sina, cosa + uz*uz*(1-cosa), 0,
						 0, 0, 0, 1
						 );;
	}
	
protected:
    //------------------------------------------------------- protected data
    //------------- any subclasses of Object3D will have access to this data

	//! transformation matrix from object to world coordinate system
	Matrix4 m_transformationMatrix;
};


//=============================================================================
#endif // OBJECT3D_HH defined
//=============================================================================

