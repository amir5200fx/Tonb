#include "ReportTable.hxx"

#include <Wt/WText.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WTableView.h>

namespace tnbLib
{

	class NumericItem
		: public Wt::WStandardItem
	{

	public:

		std::unique_ptr<Wt::WStandardItem> clone() const override
		{
			return std::make_unique<NumericItem>();
		}

		void setData(const Wt::cpp17::any& data, Wt::ItemDataRole role  = Wt::ItemDataRole::User )
		{
			Wt::cpp17::any dt;

			if (role == Wt::ItemDataRole::Edit) {
				std::string s = Wt::asString(data).toUTF8();
				char *endptr;
				double d = strtod(s.c_str(), &endptr);
				if (*endptr == 0)
					dt = Wt::cpp17::any(d);
				else
					dt = data;
			}

			WStandardItem::setData(data, role);
		}
	};


}



#include <math.h>
#include <fstream>

//#include "ChartsExample.h"
//#include "ChartConfig.h"
//#include "CsvUtil.h"

#include <Wt/WApplication.h>
#include <Wt/WDate.h>
#include <Wt/WEnvironment.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WText.h>

#include <Wt/WBorderLayout.h>
#include <Wt/WFitLayout.h>

#include <Wt/WStandardItem.h>
#include <Wt/WTableView.h>

#include <Wt/Chart/WCartesianChart.h>
#include <Wt/Chart/WPieChart.h>

#include "CsvUtil.hxx"

using namespace Wt;
using namespace Wt::Chart;

namespace tnbLib
{

	std::shared_ptr<WAbstractItemModel> readCsvFile(const std::string &fname,
		WContainerWidget *parent)
	{
		std::shared_ptr<WStandardItemModel> model
			= std::make_shared<WStandardItemModel>(0, 0);
		std::unique_ptr<NumericItem> prototype
			= std::make_unique<NumericItem>();
		model->setItemPrototype(std::move(prototype));
		std::ifstream f(fname.c_str());

		if (f) {
			readFromCsv(f, model.get());

			for (int row = 0; row < model->rowCount(); ++row)
				for (int col = 0; col < model->columnCount(); ++col) {
					model->item(row, col)->setFlags(ItemFlag::Selectable | ItemFlag::Editable);

					/*
					  Example of tool tips (disabled here because they are not updated
					  when editing data)
					 */

					 /*
					 WString toolTip = asString(model->headerData(col)) + ": "
					   + asString(model->item(row, col)->data(DisplayRole), "%.f");
					 model->item(row, col)->setToolTip(toolTip);
					  */
				}

			return model;
		}
		else {
			WString error(WString::tr("error-missing-data"));
			error.arg(fname, CharEncoding::UTF8);
			parent->addWidget(std::make_unique<WText>(error));
			return 0;
		}
	}
}

tnbLib::ReportTable::ReportTable()
	: WContainerWidget()
{
	/*this->addWidget(std::make_unique<Wt::WText>(Wt::WString::tr("Report")));

	auto model = std::make_shared<Wt::WStandardItemModel>();
	auto prototype = std::make_unique<NumericItem>();

	model->setItemPrototype(std::move(prototype));

	model->insertColumns(model->columnCount(), 2);
	model->setHeaderData(0, Wt::WString("Item"));
	model->setHeaderData(1, Wt::WString("Sales"));

	auto w = this->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto table = w->addWidget(std::make_unique<Wt::WTableView>());

	table->setMargin(10, Wt::Side::Top | Wt::Side::Bottom);
	table->setMargin(Wt::WLength::Auto, Wt::Side::Left | Wt::Side::Right);
	table->setSortingEnabled(true);
	table->setModel(model);
	table->setColumnWidth(1, 100);
	table->setRowHeight(22);*/

	/*std::shared_ptr<WAbstractItemModel> model1
		= readCsvFile(WApplication::appRoot() + "category.csv", this);*/

	this->addWidget(std::make_unique<WText>(WString::tr("pie chart")));

	std::shared_ptr<WStandardItemModel> model
		= std::make_shared<WStandardItemModel>();
	std::unique_ptr<NumericItem> prototype
		= std::make_unique<NumericItem>();
	model->setItemPrototype(std::move(prototype));

	//headers
	model->insertColumns(model->columnCount(), 2);
	model->setHeaderData(0, WString("Item"));
	model->setHeaderData(1, WString("Sales"));

	//data
	model->insertRows(model->rowCount(), 6);
	int row = 0;
	model->setData(row, 0, WString("Blueberry"));
	model->setData(row, 1, 120);
	// model->setData(row, 1, WString("Blueberry"), ToolTipRole);
	row++;
	model->setData(row, 0, WString("Cherry"));
	model->setData(row, 1, 30);
	row++;
	model->setData(row, 0, WString("Apple"));
	model->setData(row, 1, 260);
	row++;
	model->setData(row, 0, WString("Boston Cream"));
	model->setData(row, 1, 160);
	row++;
	model->setData(row, 0, WString("Other"));
	model->setData(row, 1, 40);
	row++;
	model->setData(row, 0, WString("Vanilla Cream"));
	model->setData(row, 1, 120);
	row++;

	//set all items to be editable and selectable
	for (int row = 0; row < model->rowCount(); ++row)
		for (int col = 0; col < model->columnCount(); ++col)
			model->item(row, col)->setFlags(ItemFlag::Selectable | ItemFlag::Editable);

	WContainerWidget *w = this->addWidget(std::make_unique<WContainerWidget>());
	WTableView* table = w->addWidget(std::make_unique<WTableView>());

	table->setMargin(10, Side::Top | Side::Bottom);
	table->setMargin(WLength::Auto, Side::Left | Side::Right);
	table->setSortingEnabled(true);
	table->setModel(model);
	table->setColumnWidth(1, 100);
	table->setRowHeight(22);

	if (WApplication::instance()->environment().ajax()) {
		table->resize(150 + 100 + 14, 20 + 6 * 22);
		table->setEditTriggers(EditTrigger::SingleClicked);
	}
	else {
		table->resize(150 + 100 + 14, WLength::Auto);
		table->setEditTriggers(EditTrigger::None);
	}

	/*
  * Create the pie chart.
  */
	WPieChart *chart = this->addWidget(std::make_unique<WPieChart>());
	chart->setModel(model);       // set the model
	chart->setLabelsColumn(0);    // set the column that holds the labels
	chart->setDataColumn(1);      // set the column that holds the data

	// configure location and type of labels
	chart->setDisplayLabels(LabelOption::Outside | LabelOption::TextLabel | LabelOption::TextPercentage);

	// enable a 3D and shadow effect
	chart->setPerspectiveEnabled(true, 0.2);
	chart->setShadowEnabled(true);

	// explode the first item
	chart->setExplode(0, 0.3);

	chart->resize(800, 300); // WPaintedWidget must be given an explicit size

	chart->setMargin(10, Side::Top | Side::Bottom);            // add margin vertically
	chart->setMargin(WLength::Auto, Side::Left | Side::Right); // center horizontally
}