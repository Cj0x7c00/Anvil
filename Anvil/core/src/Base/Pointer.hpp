#pragma once

#include <memory>

namespace Anvil
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	/// <summary>
	/// Unique ptr
	/// </summary>
	/// <typeparam name="T">Object</typeparam>
	/// <typeparam name="...Args">Object Args</typeparam>
	/// <param name="...args"></param>
	/// <returns>Unique ptr of object</returns>
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	/// <summary>
	/// Shared ptr
	/// </summary>
	/// <typeparam name="T">Object</typeparam>
	/// <typeparam name="...Args">Object Args</typeparam>
	/// <param name="...args"></param>
	/// <returns>Shared ptr of object</returns>
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
