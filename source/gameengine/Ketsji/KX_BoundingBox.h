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
 * Contributor(s): Tristan Porteries.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef __KX_BOUNDING_BOX_H__
#define __KX_BOUNDING_BOX_H__

#ifdef WITH_PYTHON

#include "EXP_PyObjectPlus.h"
#include "mathfu.h"

class KX_GameObject;

#ifdef USE_MATHUTILS
/// Setup mathutils callbacks.
void KX_BoundingBox_Mathutils_Callback_Init();
#endif

/** \brief Temporary python proxy class to alterate the game object
 * bounding box/AABB. Any instance of this class is owned by python.
 */
class KX_BoundingBox : public PyObjectPlus
{
	Py_Header
protected:
	/// The game object owner of this bounding box proxy.
	KX_GameObject *m_owner;
	/// The game object owner python proxy.
	PyObject *m_proxy;

public:
	KX_BoundingBox(KX_GameObject *owner);
	virtual ~KX_BoundingBox();

	/** Return true if the object owner is still valid.
	 * Else return false and print a python error.
	 */
	bool IsValidOwner();

	/// Return AABB max.
	const MT_Vector3& GetMax() const;
	/// Return AABB min.
	const MT_Vector3& GetMin() const;
	/// Return AABB center.
	const MT_Vector3 GetCenter() const;
	/// Return AABB radius.
	float GetRadius() const;
	/// Set AABB max, return false if the max is lesser than min.
	bool SetMax(MT_Vector3 max);
	/// Set AABB min, return true if the max is greater than max.
	bool SetMin(MT_Vector3 min);

	virtual PyObject *py_repr();

	static PyObject *pyattr_get_min(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int pyattr_set_min(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject *pyattr_get_max(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int pyattr_set_max(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject *pyattr_get_center(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject *pyattr_get_radius(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject *pyattr_get_auto_update(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int pyattr_set_auto_update(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
};

#endif  // WITH_PYTHON

#endif  // __KX_BOUNDING_BOX_H__
