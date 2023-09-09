#pragma once

namespace Anvil {

	class AlphaNum
	{
	public:
		AlphaNum();
		AlphaNum(std::string alnum);
		AlphaNum(const AlphaNum&) = default;

		operator std::string() const { return m_AlphaNum; }
	private:
		std::string m_AlphaNum;
	};

}


template <typename T> struct Hash;

template<>
struct Hash<Anvil::AlphaNum>
{
    std::string operator()(const Anvil::AlphaNum& alnum) const
    {
        return (std::string)alnum;
    }
};

