#include "MeshComponent.h"

#include "Scene.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* pOwner) : Component(pOwner), mMesh(nullptr), mTextureIndex(0)
{
	mMesh = new Mesh();
	Scene::ActiveScene->GetRenderer().AddMesh(this);
}

MeshComponent::~MeshComponent()
{
	Scene::ActiveScene->GetRenderer().RemoveMesh(this);
}
void MeshComponent::SetMesh(Mesh& pMesh)
{
	mMesh = &pMesh;
}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
	mTextureIndex = pTextureIndex;
}

void MeshComponent::Draw(Matrix4Row viewProj)
{
    if (mMesh)
    {
        Matrix4Row wt = mOwner->GetWorldTransform();
        mMesh->GetShaderProgram().Use();
        mMesh->GetShaderProgram().setMatrix4Row("uViewProj", viewProj);
        mMesh->GetShaderProgram().setMatrix4Row("uWorldTransform", wt);
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if (t) t->SetActive();
        mMesh->GetVertexArray()->SetActive();
        glDrawElements(GL_TRIANGLES, mMesh->GetVertexArray()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

