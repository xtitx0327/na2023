#include "xtreader.h"
#include <fstream>

XTReader :: XTReader (const char *filename) {
    std :: ifstream i (filename);
    i >> data;
    if (!data.contains ("splineType") || !data.contains ("order") || !data.contains ("dimension") || !data.contains ("points"))
        throw "Invalid JSON file";
    if (data["splineType"] != "BSpline" && data["splineType"] != "PPSpline")
        throw "Invalid spline type";
    if (data["order"] < 1 || data["order"] > 3)
        throw "Invalid order";
    if (data["dimension"] < 1)
        throw "Invalid dimension";
    if (data["points"].size () < 2)
        throw "Invalid points";
}