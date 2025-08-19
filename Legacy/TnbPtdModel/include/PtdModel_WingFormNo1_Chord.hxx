#pragma once
#ifndef _PtdModel_WingFormNo1_Chord_Header
#define _PtdModel_WingFormNo1_Chord_Header

#include <PtdModel_WingFormMakerNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class WingFormNo1_Chord
			: public PtdModel_WingFormMakerNo1
		{

		public:

			enum class Parameters
			{
				rootChord = 0
			};

			static TnbPtdModel_EXPORT word ROOT_CHORD;

		private:

			/*Private Data*/

			word theParameter_;


			//- private functions and operators

			TnbPtdModel_EXPORT void Init();

		public:

			static TnbPtdModel_EXPORT word TypeName_;

			//- default constructor

			WingFormNo1_Chord()
			{
				Init();
			}

			//- constructors


			//- public functions and operators


			TnbPtdModel_EXPORT Standard_Integer NbParameters() const override;
			TnbPtdModel_EXPORT word GetTypeName() const override;

			TnbPtdModel_EXPORT word Parameter(const Standard_Integer theIndex) const override;
			inline word Parameter(const Parameters) const;

			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Form> CreateForm() const override;
			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_Profile>
				CreateProfile
				(
					const std::shared_ptr<PtdModel_GlobalPars>&,
					const std::shared_ptr<PtdModel_Form>&
				) const override;
		};
	}
}

#include <PtdModel_WingFormNo1_ChordI.hxx>

#endif // !_PtdModel_WingFormNo1_Chord_Header
