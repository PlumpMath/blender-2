/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Mitchell Stokes
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "GPU_glew.h"

#include <stdio.h>


#include "RAS_OpenGLLight.h"
#include "RAS_Rasterizer.h"
#include "RAS_ICanvas.h"

#include "MT_CmMatrix4x4.h"

#include "KX_Camera.h"
#include "KX_Light.h"
#include "KX_Scene.h"

#include "DNA_lamp_types.h"
#include "DNA_scene_types.h"

#include "GPU_lamp.h"
#include "GPU_material.h"

#include "BLI_math.h"

RAS_OpenGLLight::RAS_OpenGLLight(RAS_Rasterizer *ras)
	:m_rasterizer(ras)
{
}

RAS_OpenGLLight::~RAS_OpenGLLight()
{
	GPULamp *lamp;
	KX_LightObject *kxlight = (KX_LightObject *)m_light;
	Lamp *la = (Lamp *)kxlight->GetBlenderObject()->data;

	if ((lamp = GetGPULamp())) {
		float obmat[4][4] = {{0}};
		GPU_lamp_update(lamp, 0, 0, obmat);
		GPU_lamp_update_distance(lamp, la->dist, la->att1, la->att2, la->coeff_const, la->coeff_lin, la->coeff_quad);
		GPU_lamp_update_spot(lamp, la->spotsize, la->spotblend);
	}
}

bool RAS_OpenGLLight::ApplyFixedFunctionLighting(KX_Scene *kxscene, int oblayer, int slot)
{
	//KX_Scene *lightscene = (KX_Scene *)m_scene;
	//KX_LightObject *kxlight = (KX_LightObject *)m_light;
	//float vec[4];
	//int scenelayer = ~0;

	//if (kxscene && kxscene->GetBlenderScene())
	//	scenelayer = kxscene->GetBlenderScene()->lay;

	///* only use lights in the same layer as the object */
	//if (!(m_layer & oblayer))
	//	return false;
	///* only use lights in the same scene, and in a visible layer */
	//if (kxscene != lightscene || !(m_layer & scenelayer))
	//	return false;

	//// lights don't get their openGL matrix updated, do it now
	//if (kxlight->GetSGNode()->IsDirty())
	//	kxlight->GetOpenGLMatrix();

	//MT_CmMatrix4x4& worldmatrix = *kxlight->GetOpenGLMatrixPtr();

	//vec[0] = worldmatrix(0, 3);
	//vec[1] = worldmatrix(1, 3);
	//vec[2] = worldmatrix(2, 3);
	//vec[3] = 1.0f;

	//if (m_type == RAS_ILightObject::LIGHT_SUN) {

	//	vec[0] = worldmatrix(0, 2);
	//	vec[1] = worldmatrix(1, 2);
	//	vec[2] = worldmatrix(2, 2);
	//	//vec[0] = base->object->obmat[2][0];
	//	//vec[1] = base->object->obmat[2][1];
	//	//vec[2] = base->object->obmat[2][2];
	//	vec[3] = 0.0f;
	//	glLightfv((GLenum)(GL_LIGHT0 + slot), GL_POSITION, vec);
	//}
	//else {
	//	//vec[3] = 1.0;
	//	glLightfv((GLenum)(GL_LIGHT0 + slot), GL_POSITION, vec);
	//	glLightf((GLenum)(GL_LIGHT0 + slot), GL_CONSTANT_ATTENUATION, 1.0f);
	//	glLightf((GLenum)(GL_LIGHT0 + slot), GL_LINEAR_ATTENUATION, m_att1 / m_distance);
	//	// without this next line it looks backward compatible.
	//	//attennuation still is acceptable
	//	glLightf((GLenum)(GL_LIGHT0 + slot), GL_QUADRATIC_ATTENUATION, m_att2 / (m_distance * m_distance));

	//	if (m_type == RAS_ILightObject::LIGHT_SPOT) {
	//		vec[0] = -worldmatrix(0, 2);
	//		vec[1] = -worldmatrix(1, 2);
	//		vec[2] = -worldmatrix(2, 2);
	//		//vec[0] = -base->object->obmat[2][0];
	//		//vec[1] = -base->object->obmat[2][1];
	//		//vec[2] = -base->object->obmat[2][2];
	//		glLightfv((GLenum)(GL_LIGHT0 + slot), GL_SPOT_DIRECTION, vec);
	//		glLightf((GLenum)(GL_LIGHT0 + slot), GL_SPOT_CUTOFF, m_spotsize / 2.0f);
	//		glLightf((GLenum)(GL_LIGHT0 + slot), GL_SPOT_EXPONENT, 128.0f * m_spotblend);
	//	}
	//	else {
	//		glLightf((GLenum)(GL_LIGHT0 + slot), GL_SPOT_CUTOFF, 180.0f);
	//	}
	//}

	//if (m_nodiffuse) {
	//	vec[0] = vec[1] = vec[2] = vec[3] = 0.0f;
	//}
	//else {
	//	vec[0] = m_energy * m_color[0];
	//	vec[1] = m_energy * m_color[1];
	//	vec[2] = m_energy * m_color[2];
	//	vec[3] = 1.0f;
	//}

	//glLightfv((GLenum)(GL_LIGHT0 + slot), GL_DIFFUSE, vec);
	//if (m_nospecular) {
	//	vec[0] = vec[1] = vec[2] = vec[3] = 0.0f;
	//}
	//else if (m_nodiffuse) {
	//	vec[0] = m_energy * m_color[0];
	//	vec[1] = m_energy * m_color[1];
	//	vec[2] = m_energy * m_color[2];
	//	vec[3] = 1.0f;
	//}

	//glLightfv((GLenum)(GL_LIGHT0 + slot), GL_SPECULAR, vec);
	//glEnable((GLenum)(GL_LIGHT0 + slot));

	GPULamp *lamp = GetGPULamp();
	KX_LightObject *kxlight = (KX_LightObject *)m_light;

	if (lamp != nullptr && kxlight->GetSGNode()) {
		float obmat[4][4];
		// lights don't get their openGL matrix updated, do it now
		if (kxlight->GetSGNode()->IsDirty())
			kxlight->GetOpenGLMatrix();
		float *dobmat = kxlight->GetOpenGLMatrixPtr()->getPointer();

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++, dobmat++)
				obmat[i][j] = (float)*dobmat;
		int hide = kxlight->GetVisible() ? 0 : 1;
		GPU_lamp_update(lamp, m_layer, hide, obmat);
		GPU_lamp_update_colors(lamp, m_color[0], m_color[1],
			m_color[2], m_energy);
		GPU_lamp_update_distance(lamp, m_distance, m_att1, m_att2, m_coeff_const, m_coeff_lin, m_coeff_quad);
		GPU_lamp_update_spot(lamp, m_spotsize, m_spotblend);

		Lamp *la = (Lamp *)kxlight->GetBlenderObject()->data;
		float mat[4][4], scale[3], power;

		/* Position */
		copy_v3_v3(m_lightData.position, kxlight->NodeGetWorldPosition().getValue());

		/* Color */
		copy_v3_v3(m_lightData.color, m_color);

		/* Influence Radius */
		m_lightData.dist = la->dist;

		/* Vectors */
		normalize_m4_m4_ex(mat, obmat, scale);
		copy_v3_v3(m_lightData.forwardvec, mat[2]);
		normalize_v3(m_lightData.forwardvec);
		negate_v3(m_lightData.forwardvec);

		copy_v3_v3(m_lightData.rightvec, mat[0]);
		normalize_v3(m_lightData.rightvec);

		copy_v3_v3(m_lightData.upvec, mat[1]);
		normalize_v3(m_lightData.upvec);

		/* Spot size & blend */
		if (la->type == LA_SPOT) {
			m_lightData.sizex = scale[0] / scale[2];
			m_lightData.sizey = scale[1] / scale[2];
			m_lightData.spotsize = cosf(la->spotsize * 0.5f);
			m_lightData.spotblend = (1.0f - m_lightData.spotsize) * la->spotblend;
			m_lightData.radius = max_ff(0.001f, la->area_size);
		}
		else if (la->type == LA_AREA) {
			m_lightData.sizex = max_ff(0.0001f, la->area_size * scale[0] * 0.5f);
			if (la->area_shape == LA_AREA_RECT) {
				m_lightData.sizey = max_ff(0.0001f, la->area_sizey * scale[1] * 0.5f);
			}
			else {
				m_lightData.sizey = max_ff(0.0001f, la->area_size * scale[1] * 0.5f);
			}
		}
		else {
			m_lightData.radius = max_ff(0.001f, la->area_size);
		}

		/* Make illumination power constant */
		if (la->type == LA_AREA) {
			power = 1.0f / (m_lightData.sizex * m_lightData.sizey * 4.0f * M_PI) /* 1/(w*h*Pi) */
				* 80.0f; /* XXX : Empirical, Fit cycles power */
		}
		else if (la->type == LA_SPOT || la->type == LA_LOCAL) {
			power = 1.0f / (4.0f * m_lightData.radius * m_lightData.radius * M_PI * M_PI) /* 1/(4*r�*Pi�) */
				* M_PI * M_PI * M_PI * 10.0; /* XXX : Empirical, Fit cycles power */

			/* for point lights (a.k.a radius == 0.0) */
			// power = M_PI * M_PI * 0.78; /* XXX : Empirical, Fit cycles power */
		}
		else {
			power = 1.0f;
		}
		mul_v3_fl(m_lightData.color, power * m_energy);

		/* Lamp Type */
		m_lightData.lamptype = (float)la->type;

		/* No shadow by default */
		m_lightData.shadowid = -1.0f;

		m_lightData.spec = 50.0f;
	}
	return true;
}

EEVEE_Light RAS_OpenGLLight::GetEeveeLightData()
{
	return m_lightData;
}

GPULamp *RAS_OpenGLLight::GetGPULamp()
{
	KX_LightObject *kxlight = (KX_LightObject *)m_light;

	return GPU_lamp_from_blender(kxlight->GetScene()->GetBlenderScene(), kxlight->GetBlenderObject(), kxlight->GetBlenderGroupObject());
}

bool RAS_OpenGLLight::HasShadowBuffer()
{
	GPULamp *lamp;

	if ((lamp = GetGPULamp()))
		return GPU_lamp_has_shadow_buffer(lamp);
	else
		return false;
}


bool RAS_OpenGLLight::NeedShadowUpdate()
{
	if (!m_staticShadow)
		return true;
	return m_requestShadowUpdate;
}

int RAS_OpenGLLight::GetShadowBindCode()
{
	GPULamp *lamp;
	
	if ((lamp = GetGPULamp()))
		return GPU_lamp_shadow_bind_code(lamp);
	return -1;
}

MT_Matrix4x4 RAS_OpenGLLight::GetViewMat()
{
	GPULamp *lamp = GetGPULamp();
	if (lamp) {
		return MT_Matrix4x4(GPU_lamp_get_viewmat(lamp));
	}
	return MT_Matrix4x4::Identity();
}

MT_Matrix4x4 RAS_OpenGLLight::GetWinMat()
{
	GPULamp *lamp = GetGPULamp();
	if (lamp) {
		return MT_Matrix4x4(GPU_lamp_get_winmat(lamp));
	}
	return MT_Matrix4x4::Identity();
}

MT_Matrix4x4 RAS_OpenGLLight::GetShadowMatrix()
{
	GPULamp *lamp;

	if ((lamp = GetGPULamp()))
		return MT_Matrix4x4(GPU_lamp_dynpersmat(lamp));
	MT_Matrix4x4 mat;
	mat.setIdentity();
	return mat;
}

int RAS_OpenGLLight::GetShadowLayer()
{
	GPULamp *lamp;

	if ((lamp = GetGPULamp()))
		return GPU_lamp_shadow_layer(lamp);
	else
		return 0;
}

void RAS_OpenGLLight::BindShadowBuffer(RAS_ICanvas *canvas, KX_Camera *cam, MT_Transform& camtrans)
{
	GPULamp *lamp;
	float viewmat[4][4], winmat[4][4];
	int winsize;

	/* bind framebuffer */
	lamp = GetGPULamp();
	GPU_lamp_shadow_buffer_bind(lamp, viewmat, &winsize, winmat);

	if (GPU_lamp_shadow_buffer_type(lamp) == LA_SHADMAP_VARIANCE) {
		m_rasterizer->SetShadowMode(RAS_Rasterizer::RAS_SHADOW_VARIANCE);
	}
	else {
		m_rasterizer->SetShadowMode(RAS_Rasterizer::RAS_SHADOW_SIMPLE);
	}

	/* GPU_lamp_shadow_buffer_bind() changes the viewport, so update the canvas */
	canvas->UpdateViewPort(0, 0, winsize, winsize);

	/* setup camera transformation */
	MT_Matrix4x4 modelviewmat((float *)viewmat);
	MT_Matrix4x4 projectionmat((float *)winmat);

	MT_Transform trans = MT_Transform((float *)viewmat);
	camtrans.invert(trans);

	cam->SetModelviewMatrix(modelviewmat);
	cam->SetProjectionMatrix(projectionmat);

	cam->NodeSetLocalPosition(camtrans.getOrigin());
	cam->NodeSetLocalOrientation(camtrans.getBasis());
	cam->NodeUpdateGS(0);

	/* setup rasterizer transformations */
	/* SetViewMatrix may use stereomode which we temporarily disable here */
	RAS_Rasterizer::StereoMode stereomode = m_rasterizer->GetStereoMode();
	m_rasterizer->SetStereoMode(RAS_Rasterizer::RAS_STEREO_NOSTEREO);
	m_rasterizer->SetProjectionMatrix(projectionmat);
	m_rasterizer->SetViewMatrix(modelviewmat, cam->NodeGetWorldPosition(), cam->NodeGetLocalScaling());
	m_rasterizer->SetStereoMode(stereomode);
}

void RAS_OpenGLLight::UnbindShadowBuffer()
{
	GPULamp *lamp = GetGPULamp();
	GPU_lamp_shadow_buffer_unbind(lamp);

	m_rasterizer->SetShadowMode(RAS_Rasterizer::RAS_SHADOW_NONE);

	m_requestShadowUpdate = false;
}

Image *RAS_OpenGLLight::GetTextureImage(short texslot)
{
	KX_LightObject *kxlight = (KX_LightObject *)m_light;
	Lamp *la = (Lamp *)kxlight->GetBlenderObject()->data;

	if (texslot >= MAX_MTEX || texslot < 0) {
		printf("KX_LightObject::GetTextureImage(): texslot exceeds slot bounds (0-%d)\n", MAX_MTEX - 1);
		return nullptr;
	}

	if (la->mtex[texslot])
		return la->mtex[texslot]->tex->ima;

	return nullptr;
}

void RAS_OpenGLLight::Update()
{
}

