#pragma once

#include "Shader.h"
#include <DirectXMath.h>

class ColorShader :public Shader
{
public:
    void Draw(ID3D11DeviceContext* dc, const Model* model) override;

private:
    DirectX::XMFLOAT4 currentColor;  // 現在の色を保持する
};