#include "header.h"

//Funcion para crear una grafica
int hacer_grafica(std::vector<double> x, std::vector<double> y,
                    std::wstring title, std::wstring xlabel, std::wstring ylabel, std::string image_name) {

    bool success;
	StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &x;
	series->ys = &y;
	series->linearInterpolation = true;
	series->lineType = toVector(L"dashed");
	series->lineThickness = 2;
	series->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(title.c_str());
	settings->xLabel = toVector(xlabel.c_str());
	settings->yLabel = toVector(ylabel.c_str());
	settings->scatterPlotSeries->push_back(series);

	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

	if(success){
		std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
		WriteToFile(pngdata, image_name);
		DeleteImage(imageReference->image);
	}else{
		std:: cerr << "Graphic Error: ";
		for(wchar_t c : *errorMessage->string){
			std::wcerr << c;
		}
		std::cerr << std::endl;
	}

	FreeAllocations();

	return success ? 0 : 1;

};