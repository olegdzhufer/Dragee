#include "MenuLib.h"

void setInt(valLine* data, int val){
    data->var.count = val;
    data->TYPE = valLine::INTEGER;
}


void setBool(valLine* data, bool val){
    data->var.status = val;
    data->TYPE = valLine::BOOLING;
}


void setFloat(valLine* data, float val){
    data->var.temp = val;
    data->TYPE = valLine::FLOAT;
}
void setText(valLine* data, char* val){
    data->var.mode = val;
    data->TYPE = valLine::TEXT;
}

void setNull(valLine* data){
    data->TYPE = valLine::NULLTYPE;
}