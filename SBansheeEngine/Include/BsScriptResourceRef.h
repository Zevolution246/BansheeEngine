#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "BsTexture.h"
#include "BsScriptResource.h"
#include "BsMonoClass.h"
#include "BsRTTIType.h"

namespace BansheeEngine
{
	/**
	 * @brief	Interop class between C++ & CLR for ResourceRefBase.
	 */
	class BS_SCR_BE_EXPORT ScriptResourceRefBase : public ScriptObject<ScriptResourceRefBase>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "ResourceRefBase")

		ScriptResourceRefBase(MonoObject* instance, const WeakResourceHandle<Resource>& resource);

		/**
		 * @brief	Returns a weak handle to the resource referenced by this object.
		 */
		WeakResourceHandle<Resource> getHandle() const { return mResource; }

	private:
		WeakResourceHandle<Resource> mResource;

		/************************************************************************/
		/* 								CLR HOOKS						   		*/
		/************************************************************************/
		static bool internal_IsLoaded(ScriptResourceRefBase* nativeInstance);
		static MonoObject* internal_GetResource(ScriptResourceRefBase* nativeInstance);
		static MonoString* internal_GetUUID(ScriptResourceRefBase* thisPtr);
	};

	/**
	 * @brief	Interop class between C++ & CLR for ResourceRef.
	 */
	class BS_SCR_BE_EXPORT ScriptResourceRef : public ScriptObject<ScriptResourceRef>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "ResourceRef`1")

		/**
		 * @brief	Creates a new managed ResourceRef for the provided resource.
		 *
		 * @param	handle	Handle to the resource to wrap.
		 */
		template<class T>
		static MonoObject* create(const WeakResourceHandle<T>& handle)
		{
			MonoClass* resourceClass = ScriptResource::getClassFromTypeId(T::getRTTIStatic()->getRTTIId());
			if (resourceClass == nullptr)
				return nullptr;

			return create(resourceClass->_getInternalClass(), handle);
		}

		/**
		 * @brief	Creates a new managed ResourceRef for the provided texture.
		 *
		 * @param	handle	Handle to the texture to wrap.
		 */
		static MonoObject* create(const WeakResourceHandle<Texture>& handle, TextureType type = TEX_TYPE_2D);

	private:
		friend class ScriptResourceRefBase;

		ScriptResourceRef(MonoObject* instance);

		/**
		 * @brief	Creates a new managed ResourceRef for the provided resource type.
		 *
		 * @param	resourceClass	Managed class of the resource to reference.
		 * @param	handle			Handle to the resource to wrap.
		 */
		static MonoObject* create(::MonoClass* resourceClass, const WeakResourceHandle<Resource>& handle);
	};
}