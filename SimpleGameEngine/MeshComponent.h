#pragma once
#include "Mesh.h"

class MeshComponent : public Component
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;
public:
	MeshComponent(Actor* pOwner);
	virtual ~MeshComponent();
	virtual void Draw(Matrix4Row viewProj);
	virtual void SetMesh(Mesh& pMesh);
	void SetTextureIndex(size_t pTextureIndex);
};

