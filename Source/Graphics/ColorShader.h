#pragma once

#include "Shader.h"
#include <DirectXMath.h>

class ColorShader :public Shader
{
public:
    void Draw(ID3D11DeviceContext* dc, const Model* model) override;

private:
    DirectX::XMFLOAT4 currentColor;  // ���݂̐F��ێ�����
};