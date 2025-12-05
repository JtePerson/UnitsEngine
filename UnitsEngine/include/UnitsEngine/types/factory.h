#pragma once
#include <unordered_map>

#include "UnitsEngine/core/assert.h"

namespace units {
	template<typename KeyT, typename BaseT, typename PtrT= BaseT*, typename KeyHashT= std::hash<KeyT>>
	class Factory {
	public:
		using Function= std::function<PtrT()>;
		using Registry= std::unordered_map<KeyT, Function, KeyHashT>;
	public:
		template<typename DerivedT>
		inline constexpr void registerType(const KeyT& p_key) noexcept {
			static_assert((std::is_base_of<BaseT, DerivedT>::value && "DerivedT must inherit from Factory BaseT!"));
			_registry[p_key]= [](){
				if constexpr (std::is_same<PtrT, BaseT*>::value) {
					return new DerivedT();
				} else if constexpr (std::is_same<PtrT, std::unique_ptr<BaseT>>::value) {
					return std::make_unique<DerivedT>();
				} else if constexpr (std::is_same<PtrT, std::shared_ptr<BaseT>>::value) {
					return std::make_shared<DerivedT>();
				} else {
					static_assert("Unsupported Factory Pointer Type!");
				}
			};
		}
		inline bool hasType(const KeyT& p_key) const noexcept {
			return _registry.find(p_key) != _registry.end();
		}
		inline PtrT createType(const KeyT& p_key) const noexcept {
			UE_CORE_ASSERT((hasType(p_key) && "Factory Registry does not contain KeyT!"));
			return _registry.at(p_key)();
		}
	protected:
		Registry _registry;
	};
} // namespace units