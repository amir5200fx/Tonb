#include <Wt_DimAnalysis.hxx>

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>

tnbLib::wt::hydrostatic::DimAnalysis::DimAnalysis()
{
	theTitile_ = addWidget(std::make_unique<Wt::WText>(tr("This is my application")));
}