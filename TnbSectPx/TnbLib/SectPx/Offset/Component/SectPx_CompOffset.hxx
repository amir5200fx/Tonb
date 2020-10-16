#pragma once
#ifndef _SectPx_CompOffset_Header
#define _SectPx_CompOffset_Header

#include <SectPx_Offset.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	template<class xComp, class yComp>
	class SectPx_CompOffset
	{

		/*Private Data*/


	};

	template<>
	class SectPx_CompOffset
		<
		Standard_Real, 
		Standard_Real
		>
		: public SectPx_Offset
	{

		/*Private Data*/

		Standard_Real theX_;
		Standard_Real theY_;

	public:

		SectPx_CompOffset()
			: theX_(0)
			, theY_(0)
		{}

		SectPx_CompOffset
		(
			const Standard_Real theX, 
			const Standard_Real theY
		)
			: theX_(theX)
			, theY_(theY)
		{}

		Standard_Real xCoord() const override
		{
			return theX_;
		}

		Standard_Real yCoord() const override
		{
			return theY_;
		}

		void SetX(const Standard_Real x)
		{
			theX_ = x;
		}

		void SetY(const Standard_Real x)
		{
			theY_ = x;
		}
	};

	template<>
	class SectPx_CompOffset
		<
		Standard_Real, 
		SectPx_FieldFun
		>
		: public SectPx_Offset
	{

		/*Private Data*/

		Standard_Real theX_;

		std::weak_ptr<SectPx_FieldFun> theY_;

	public:

		SectPx_CompOffset()
			: theX_(0)
		{}

		SectPx_CompOffset
		(
			const Standard_Real x, 
			const std::shared_ptr<SectPx_FieldFun>& y
		);

		Standard_Real xCoord() const override
		{
			return theX_;
		}

		Standard_Real yCoord() const override;

		void SetX(const Standard_Real x)
		{
			theX_ = x;
		}

		void SetY(const std::shared_ptr<SectPx_FieldFun>& y)
		{
			theY_ = y;
		}
	};

	template<>
	class SectPx_CompOffset
		<
		SectPx_FieldFun,
		Standard_Real
		>
		: public SectPx_Offset
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFun> theX_;

		Standard_Real theY_;

	public:

		SectPx_CompOffset()
			: theY_(0)
		{}

		SectPx_CompOffset
		(
			const std::shared_ptr<SectPx_FieldFun>& x,
			const Standard_Real y
		);

		Standard_Real xCoord() const override;

		Standard_Real yCoord() const override
		{
			return theY_;
		}

		void SetX(const std::shared_ptr<SectPx_FieldFun>& x)
		{
			theX_ = x;
		}

		void SetY(const Standard_Real y)
		{
			theY_ = y;
		}
	};

	template<>
	class SectPx_CompOffset
		<
		SectPx_FieldFun, 
		SectPx_FieldFun
		>
		: public SectPx_Offset
	{

		/*Private Data*/

		std::weak_ptr<SectPx_FieldFun> theX_;
		std::weak_ptr<SectPx_FieldFun> theY_;

	public:

		SectPx_CompOffset()
		{}

		SectPx_CompOffset
		(
			const std::shared_ptr<SectPx_FieldFun>& x,
			const std::shared_ptr<SectPx_FieldFun>& y
		);

		Standard_Real xCoord() const override;

		Standard_Real yCoord() const override;

		void SetX(const std::shared_ptr<SectPx_FieldFun>& x)
		{
			theX_ = x;
		}

		void SetY(const std::shared_ptr<SectPx_FieldFun>& y)
		{
			theY_ = y;
		}
	};
}

#endif // !_SectPx_CompOffset_Header
