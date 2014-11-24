#include "shader/imaterial.h"
#include "shader/ishader.h"
#include "shape/ishape.h"
#include "ilightsource.h"
#include "shader/staticcolormaterial.h"
#include "shader/checkermaterial.h"


IMaterial::~IMaterial() {}
IShader::~IShader() {}
IShape::~IShape() {}
ILightSource::~ILightSource() {}
StaticColorMaterial::~StaticColorMaterial() {}
CheckerMaterial::~CheckerMaterial() {}

