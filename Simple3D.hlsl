//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D	g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;			//���[���h�s��
	float4x4    matNormal;		//���[���h�s��
	float4		diffuseColor;	// �g�U���ˌ����}�e���A���̐F
	float4		ambientColor;	// ����
	float4		specularColor;	// ���ʔ��ˁ��n�C���C�g
	float		shininess;
	bool		isTextured;		// �e�N�X�`���\���Ă��邩�ǂ���
};

cbuffer gmodel:register(b1)
{
	float4      lightPosition;
	float4      eyePosition;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float2 uv     : TEXCOORD;		//UV���W
	float4 color  : COLOR;          //�F�i���邳�j
	float4 eyev   : POSITION;       //�����x�N�g��
	float4 normal : NORMAL;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//�@������]
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = normalize(lightPosition);
	light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	//outData.color = clamp(dot(normal, light), 0, 1);


	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 0.0);     //���C�g�F�����邳  Iin
	float4 ambientSource = ambientColor;   //�A���r�G���g�W��  Ka  ���ڂ�����΂������������炱�̕ϐ��ʂɂ���Ȃ�����
	float4 diffuse;
	float4 ambient;
	float4 NL = dot(inData.normal, normalize(lightPosition));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));  //���ˌ��̔��˃x�N�g��
	//������specularColor(�X�y�L�����[�̒l�������Ă���)���|���邱�ƂŃn�C���C�g�L�̂�����n�C���C�g����
	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), shininess) * specularColor;
	
	if (isTextured == false)
	{
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientColor;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
	}


	/*if (abs(dot(inData.normal, normalize(inData.eyev))) < 0.3)
		return float4(0, 0, 0, 0);
	else
		return (diffuse + ambient + specular);*/

	return (diffuse + ambient + specular);


	//specular = pow(saturate(dot(diffues,ambient),))


	//float4 output = g_texture.Sample(g_sampler, inData.uv);
	//float4 output = g_texture.Sample(g_sampler, inData.uv);

	//�O���[�X�P�[���ϊ�
	//float grayValue = dot(output.rgb, float3(0.298912, 0.586611, 0.114478));
	//float4 grayColor = float4(grayValue, grayValue, grayValue, output.a);

	//float4 output = floor(g_texture.Sample(g_sampler, inData.uv)*8.0)/8;


	//return grayColor;

}