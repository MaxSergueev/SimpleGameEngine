#pragma once
#include "Vector3.h"
#include "Matrix4Row.h"
#include "Maths.h"

/**
 * @brief 3D transformation component for actors with position, rotation, and scale
 *
 * Transform2D manages the spatial properties of actors including position, rotation,
 * and scale in 3D space. Despite the "2D" name, it provides full 3D transformation
 * capabilities using quaternions for rotation and matrix calculations for world
 * transforms. It includes optimization through dirty flagging to avoid unnecessary
 * matrix recalculations.
 */
class Transform2D
{
private:
    Vector3 mPosition;          ///< World position of the transform
    Vector3 mScale;             ///< Scale factors for each axis
    Quaternion mRotation;       ///< Rotation represented as a quaternion
    Matrix4Row mWorldTransform; ///< Cached world transformation matrix
    bool mNeedsUpdate;          ///< Flag indicating if world transform needs recalculation

public:
    /**
     * @brief Default constructor - initializes to identity transform
     */
    Transform2D();

    /**
     * @brief Default destructor
     */
    ~Transform2D() = default;

    /**
     * @brief Sets the world position
     * @param pPosition New position in world coordinates
     */
    void SetPosition(Vector3 pPosition) { mPosition = pPosition; mNeedsUpdate = true; }

    /**
     * @brief Sets the scale factors
     * @param pScale New scale values for each axis
     */
    void SetScale(Vector3 pScale) { mScale = pScale; mNeedsUpdate = true; }

    /**
     * @brief Sets rotation from Euler angles
     * @param pRotation Euler angles in degrees (X, Y, Z order)
     */
    void SetRotation(Vector3 pRotation);

    /**
     * @brief Gets the current world position
     * @return Current position vector
     */
    Vector3 GetPosition() const { return mPosition; }

    /**
     * @brief Gets the current scale factors
     * @return Current scale vector
     */
    Vector3 GetScale() const { return mScale; }

    /**
     * @brief Gets the current rotation quaternion
     * @return Current rotation as quaternion
     */
    Quaternion GetRotation() const { return mRotation; }

    /**
     * @brief Gets the cached world transformation matrix
     * @return 4x4 world transformation matrix
     */
    Matrix4Row GetWorldTransform() const { return mWorldTransform; }

    /**
     * @brief Moves the transform by the specified offset
     * @param pMovement Vector to add to current position
     */
    void Translate(Vector3 pMovement);

    /**
     * @brief Rotates around an arbitrary axis
     * @param pAxis Axis of rotation (will be normalized)
     * @param pAngle Rotation angle in degrees
     */
    void RotateAroundAxis(Vector3 pAxis, float pAngle);

    /**
     * @brief Applies rotation from Euler angles
     * @param pRotation Euler angles in degrees to add to current rotation
     */
    void Rotate(Vector3 pRotation);

    /**
     * @brief Rotates around the X-axis
     * @param xRotation Rotation angle in degrees
     */
    void RotateX(float xRotation);

    /**
     * @brief Rotates around the Y-axis
     * @param yRotation Rotation angle in degrees
     */
    void RotateY(float yRotation);

    /**
     * @brief Rotates around the Z-axis
     * @param zRotation Rotation angle in degrees
     */
    void RotateZ(float zRotation);

    /**
     * @brief Recalculates the world transformation matrix if needed
     */
    void ComputeWorldTransform();

    /**
     * @brief Gets the right direction vector in world space
     * @return Normalized right vector (positive X direction)
     */
    Vector3 Right() const { return Vector3::Transform(Vector3::unitX, mRotation); }

    /**
     * @brief Gets the up direction vector in world space
     * @return Normalized up vector (positive Y direction)
     */
    Vector3 Up() const { return Vector3::Transform(Vector3::unitY, mRotation); }

    /**
     * @brief Gets the forward direction vector in world space
     * @return Normalized forward vector (positive Z direction)
     */
    Vector3 Forward() const { return Vector3::Transform(Vector3::unitZ, mRotation); }
};
