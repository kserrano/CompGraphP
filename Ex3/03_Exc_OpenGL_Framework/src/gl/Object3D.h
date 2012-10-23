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
		Matrix4 translationMatrix = m_transformationMatrix.operator*(getTranslationMatrix(_trans));
		// ((( Exercise 3.4 )))
	}
	
	
	//! translates the object in the object coordinate systems
	void translateObject( const Vector3 & _trans )
	{
		Matrix4 translationMatrix = getTranslationMatrix(_trans).operator*(m_transformationMatrix);
		// ((( Exercise 3.4 )))

	}
	
	//! scales the object in the world coordinate system
	void scaleWorld( const Vector3 & _scl )
	{
        Matrix4 scaleMatrix = getScaleMatrix(_scl);
		// ((( Exercise 3.4 )))
	}

	//! scales the object in the object coordinate systems
	void scaleObject( const Vector3 & _scl )
	{
        Matrix4 scaleMatrix = getScaleMatrix(_scl);
		// ((( Exercise 3.4 )))
	}

	//! rotates the object in the world coordinate system
	void rotateWorld( const Vector3& _axis, float _angle )
	{
        Matrix4 rotationMatrix = getRotationMatrix(_axis,_angle);
		// ((( Exercise 3.4 )))

	}

	//! rotates the object in the object coordinate system
	void rotateObject( const Vector3& _axis, float _angle )
	{
        Matrix4 rotationMatrix = getRotationMatrix(_axis,_angle);
		// ((( Exercise 3.4 )))
	}


	//! rotates the object around an arbitrary axis in world coordinate system
	void rotateAroundAxisWorld( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        Matrix4 rotationMatrix = getRotationMatrix(_axis,_angle);
		// ((( Exercise 3.4 )))
	}

	//! rotates the object around an arbitrary axis in object coordinate system
	void rotateAroundAxisObject( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        Matrix4 rotationMatrix = getRotationMatrix(_axis,_angle);
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
		
		Matrix4 scaleMatrix;
        
		// ((( Exercise 3.4 )))
        scaleMatrix.loadIdentity();
		
		return scaleMatrix;
	}
	
	//! calculate rotation matrix from rotation axis and angle in radian
	static Matrix4 getRotationMatrix(const Vector3 & axis, double angle) {
		double cosa = cos(angle);
		double sina = sin(angle);
		Matrix4 rotationMatrix;

		// ((( Exercise 3.4 )))
		rotationMatrix.loadIdentity();
        
		return rotationMatrix;
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

