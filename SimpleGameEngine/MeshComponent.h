#pragma once
#include "Mesh.h"

/**
 * @brief Component that renders 3D meshes for actors
 *
 * MeshComponent provides 3D mesh rendering functionality for actors,
 * managing the association between an actor and its visual mesh representation.
 * It handles mesh assignment, texture indexing, and rendering operations
 * within the component system architecture.
 */
class MeshComponent : public Component
{
protected:
    Mesh* mMesh;            ///< Pointer to the mesh data to render
    size_t mTextureIndex;   ///< Index of the texture to use from the mesh's texture array

public:
    /**
     * @brief Constructs a mesh component for the specified actor
     * @param pOwner The actor that owns this component
     */
    MeshComponent(Actor* pOwner);

    /**
     * @brief Virtual destructor - removes component from renderer
     */
    virtual ~MeshComponent();

    /**
     * @brief Renders the mesh with the specified view-projection matrix
     * @param viewProj The combined view and projection matrix for rendering
     */
    virtual void Draw(Matrix4Row viewProj);

    /**
     * @brief Sets the mesh to be rendered by this component
     * @param pMesh Reference to the mesh object to render
     */
    virtual void SetMesh(Mesh& pMesh);

    /**
     * @brief Gets the currently assigned mesh
     * @return Pointer to the mesh object, or nullptr if none assigned
     */
    virtual Mesh* GetMesh();

    /**
     * @brief Sets which texture index to use from the mesh's texture array
     * @param pTextureIndex Index of the texture to use for rendering
     */
    void SetTextureIndex(size_t pTextureIndex);
};