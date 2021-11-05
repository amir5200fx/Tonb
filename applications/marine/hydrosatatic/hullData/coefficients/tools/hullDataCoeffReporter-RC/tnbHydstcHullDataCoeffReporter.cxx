#include "ReportTable.hxx"

#include <Wt/WApplication.h>

namespace tnbLib
{

	class ReportApplication
		: public Wt::WApplication
	{

	public:

		ReportApplication(const Wt::WEnvironment& env)
			: Wt::WApplication(env)
		{
			setTitle("Hydrostatic data report");

			setCssTheme("polished");

			root()->setPadding(10);
			root()->resize(Wt::WLength::Auto, Wt::WLength::Auto);

			root()->addWidget(std::make_unique<ReportTable>());
		}
	};

	std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
	{
		return std::make_unique<ReportApplication>(env);
	}
}

int main(int argc, char** argv)
{
	return Wt::WRun(argc, argv, &tnbLib::createApplication);
}