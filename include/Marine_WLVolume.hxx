//#pragma once
//#ifndef _Marine_WLVolume_Header
//#define _Marine_WLVolume_Header
//
//#include <Global_Done.hxx>
//
//#include <memory>
//
//namespace tnbLib
//{
//
//	// Forward Declarations
//	class Geo_xDistb;
//	class Marine_Graph;
//	class Marine_Body;
//	class Marine_Domain;
//
//	class Marine_WLVolume
//		: public Global_Done
//	{
//
//		/*Private Data*/
//
//		std::shared_ptr<Marine_Domain> theDomain_;
//		std::shared_ptr<Marine_Body> theBody_;
//		std::shared_ptr<Geo_xDistb> theZ_;
//
//		std::shared_ptr<Marine_Graph> theGraph_;
//
//
//		auto& ChangeGraph()
//		{
//			return theGraph_;
//		}
//
//	public:
//
//		Marine_WLVolume();
//
//		Marine_WLVolume
//		(
//			const std::shared_ptr<Geo_xDistb>& theZ,
//			const std::shared_ptr<Marine_Domain>& theDomain,
//			const std::shared_ptr<Marine_Body>& theBody
//		);
//
//		const auto& Body() const
//		{
//			return theBody_;
//		}
//
//		const auto& Z() const
//		{
//			return theZ_;
//		}
//
//		const auto& Domain() const
//		{
//			return theDomain_;
//		}
//
//		const auto& Graph() const
//		{
//			return theGraph_;
//		}
//
//		void Perform();
//
//		void LoadDistrb
//		(
//			const std::shared_ptr<Geo_xDistb>& theDistrb
//		)
//		{
//			theZ_ = theDistrb;
//		}
//
//		void LoadDomain
//		(
//			const std::shared_ptr<Marine_Domain>& theDomain
//		)
//		{
//			theDomain_ = theDomain;
//		}
//
//		void LoadBody
//		(
//			const std::shared_ptr<Marine_Body>& theBody
//		)
//		{
//			theBody_ = theBody;
//		}
//	};
//}
//
//#endif // !_Marine_WLVolume_Header
