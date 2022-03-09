#include <Aft2d_CorrOptNodeSurface_Fraction.hxx>

#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>
#include <Aft2d_OptNodeSurface_Calculator.hxx>

unsigned short tnbLib::Aft2d_CorrOptNodeSurface_Fraction::verbose(0);

template<>
void tnbLib::Aft2d_CorrOptNodeSurface_Fraction::Perform
(
	const Aft_SizeCorr_FractionInfo& theInfo
)
{
	Debug_Null_Pointer(MetricMap());
	Debug_Null_Pointer(Front());

	const auto h1 = Size();
	const auto h2 = MetricMap()->CalcElementSize(P0());

	if (h2 >= h1)
	{
		CoordRef() = P0();
	}
	else
	{
		auto h = h1;

		const auto delta = theInfo.Delta();
		const auto frac = (h1 - h2) / h1;

		if (frac <= delta)
		{
			/*continue*/
		}
		else
		{
			const auto w = theInfo.Coeff();
			h = w * h1 + ((Standard_Real)1.0 - w)*h2;
		}

		Debug_If_Condition_Message(NOT NodeCalculator(), "no calculator has been loaded!");

		auto& nodeCalculator = *NodeCalculator();
		nodeCalculator.SetFront(Front());
		nodeCalculator.SetMetricMap(MetricMap());
		nodeCalculator.SetSize(Size());

		nodeCalculator.Perform();
		Debug_If_Condition_Message(NOT nodeCalculator.IsDone(), "the algorithm is not performed!");

		CoordRef() = nodeCalculator.Coord();
	}

	IsConvergedRef() = Standard_True;
	Change_IsDone() = Standard_True;
}