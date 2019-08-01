#include "Brush.h"

#include "cairo.h"

using namespace std;
using namespace Eleusis;

BitmapBrush::BitmapBrush(string imagePath)
{
    _sourceSurface = cairo_image_surface_create_from_png(imagePath.c_str());
    _pattern = cairo_pattern_create_for_surface(_sourceSurface);
    cairo_pattern_set_extend(_pattern, cairo_extend_t::CAIRO_EXTEND_NONE);
}

BitmapBrush::~BitmapBrush()
{
    cairo_pattern_destroy(_pattern);
    cairo_surface_destroy(_sourceSurface);
}

void BitmapBrush::extension_set(BitmapBrushExtension extension)
{
    if (extension == _extend) return;
    
    _extend = extension;

    cairo_extend_t l_cairoExtend;

    switch (extension)
    {
    case BitmapBrushExtension::None:
        l_cairoExtend = cairo_extend_t::CAIRO_EXTEND_NONE;
        break;
    case BitmapBrushExtension::Pad:
        l_cairoExtend = cairo_extend_t::CAIRO_EXTEND_PAD;
        break;
    case BitmapBrushExtension::Reflect:
        l_cairoExtend = cairo_extend_t::CAIRO_EXTEND_REFLECT;
        break;
    case BitmapBrushExtension::Repeat:
        l_cairoExtend = cairo_extend_t::CAIRO_EXTEND_REPEAT;
        break;
    default:
        l_cairoExtend = cairo_extend_t::CAIRO_EXTEND_NONE;
    }

    cairo_pattern_set_extend(_pattern, l_cairoExtend);
    raiseEvent brushUpdated(this, nullptr);
}


BitmapBrushExtension BitmapBrush::extension_get()
{
    return _extend;
}

void BitmapBrush::resetAffineTransformation()
{
    if (!_isAffineTransformationApplied) return;

    _affineTransformation.setAffineMatrixToIdentity();
    _isAffineTransformationApplied = false;

    cairo_pattern_set_matrix(_pattern, _affineTransformation.getAffineMatrix());

    raiseEvent brushUpdated(this, nullptr);
}

void BitmapBrush::setAffineTransformation(AffineTransformation* affineTransformation) 
{
    _affineTransformation = *affineTransformation;
    _isAffineTransformationApplied = true;
    cairo_matrix_t l_matrix = *_affineTransformation.getAffineMatrix();
    cairo_matrix_invert(&l_matrix);
    cairo_pattern_set_matrix(_pattern, &l_matrix);

    raiseEvent brushUpdated(this, nullptr);
}

void BitmapBrush::multiplyAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation.multiplyAffineTransformation(affineTransformation);
    _isAffineTransformationApplied = true;
    cairo_matrix_t l_matrix = *_affineTransformation.getAffineMatrix();
    cairo_matrix_invert(&l_matrix);
    cairo_pattern_set_matrix(_pattern, &l_matrix);

    raiseEvent brushUpdated(this, nullptr);
}



