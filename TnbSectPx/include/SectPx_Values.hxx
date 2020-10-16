#pragma once
#ifndef _SectPx_Values_Header
#define _SectPx_Values_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class T>
	class SectPx_Values
	{

	public:

		typedef std::vector<std::shared_ptr<T>> typeList;

	private:

		/*Private Data*/

		std::shared_ptr<typeList> theValues_;


		void AllocateMemory()
		{
			theValues_ = std::make_shared<typeList>();
		}

	public:

		SectPx_Values()
		{
			AllocateMemory();
		}

		SectPx_Values(const std::shared_ptr<typeList>& theList)
			: theValues_(theList)
		{}

		SectPx_Values(std::shared_ptr<typeList>&& theList)
			: theValues_(std::move(theList))
		{}

		const auto& Value() const
		{
			return theValues_;
		}

		const auto& operator()() const
		{
			return Value();
		}

		void SetValue(const std::shared_ptr<typeList>& theList)
		{
			theValues_ = theList;
		}

		void SetValue(std::shared_ptr<typeList>&& theList)
		{
			theValues_ = std::move(theList);
		}
	};

	template<>
	class SectPx_Values<Standard_Real>
	{

	public:

		typedef std::vector<Standard_Real> realList;

	private:

		/*Private Data*/

		std::shared_ptr<realList> theValues_;


		void AllocateMemory()
		{
			theValues_ = std::make_shared<realList>();
		}

	public:

		SectPx_Values()
		{
			AllocateMemory();
		}

		SectPx_Values(const std::shared_ptr<realList>& theList)
			: theValues_(theList)
		{}

		SectPx_Values(std::shared_ptr<realList>&& theList)
			: theValues_(std::move(theList))
		{}

		const auto& Value() const
		{
			return theValues_;
		}

		const auto& operator()() const
		{
			return Value();
		}

		void SetValue(const std::shared_ptr<realList>& theList)
		{
			theValues_ = theList;
		}

		void SetValue(std::shared_ptr<realList>&& theList)
		{
			theValues_ = std::move(theList);
		}
	};

	namespace sectPxLib
	{
		typedef SectPx_Values<Standard_Real> realValues;
	}
}

#endif // !_SectPx_Values_Header
