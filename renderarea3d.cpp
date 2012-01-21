#include "renderarea3d.h"

RenderArea3D::RenderArea3D(QWidget *parent, Cellular *cellular, int z, int area_size)
    : QGLViewer(parent), RenderAreaI(cellular, z), _area_size(area_size) {}

RenderArea3D::~RenderArea3D() {
    delete _cells_painter;
}

QSize RenderArea3D::minimumSizeHint() const {
    return QSize(width(), height());
}

void RenderArea3D::drawCube(const float3 &center, const float3 &color, float alpha) {
    primitiveCube(center, .44f, color, alpha);
}

void RenderArea3D::drawCubeBorder(const float3 &center, const float3 &color, float alpha) {
    primitiveCubeBorder(center, .45f, color, alpha);
}

void RenderArea3D::drawBCube(const float3 &center, const float3 &color, float alpha) {
    drawCube(center, color, alpha);
    float3 darken(color.x * .8f, color.y * .8f, color.z * .8f);
    drawCubeBorder(center, darken, alpha);
}

void RenderArea3D::drawHalfDimer(const float3 &center, float alpha) {
    const float half_width = .25f;
    const float half_height = .05f;

    primitiveParallelogram(center, float3(half_width, half_width, half_height), float3(.9f, .9f, .9f), alpha);
}

void RenderArea3D::init() {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setRadiusAndCenter();

    _cells_painter = this->createCellsPainter();
}

void RenderArea3D::draw() {
    drawSliceSelector();
    cellular()->store(cellsPainter());
}

CellsPainter3D *RenderArea3D::createCellsPainter() {
    return new CellsPainter3D(this, cellular()->dimY() - 1);
}

void RenderArea3D::primitiveCube(const float3 &center, float half_side_length, const float3 &color, float alpha) {
    primitiveParallelogram(center, float3(half_side_length, half_side_length, half_side_length), color, alpha);
}

void RenderArea3D::primitiveCubeBorder(const float3 &center, float half_side_length, const float3 &color, float alpha) {
    primitiveParallelogramBorder(center, float3(half_side_length, half_side_length, half_side_length), 2.f, color, alpha);
}

void RenderArea3D::primitiveParallelogram(const float3 &center, const float3 &half_side_lengths, const float3 &color, float alpha) {
    setColor(color, alpha);

    glBegin(GL_QUADS);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);

    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);

    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);

    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);

    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);

    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glEnd();
}

void RenderArea3D::primitiveParallelogramBorder(const float3 &center, const float3 &half_side_lengths, float border_width,
                                                const float3 &color, float alpha)
{
    setColor(color, alpha);
    glLineWidth(border_width);

    glBegin(GL_LINE_LOOP);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y + half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z - half_side_lengths.z);
    glVertex3f(center.x + half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glVertex3f(center.x - half_side_lengths.x, center.y - half_side_lengths.y, center.z + half_side_lengths.z);
    glEnd();
}

void RenderArea3D::drawSliceSelector() {
    const float min_x = (currZ() - 1) * .5f;
    const float max_x = cellular()->dimX() + (currZ() + 1) * .5f;

    const float min_y = -cellular()->dimY() - currZ() * .5f - 1.5f;
    const float max_y = cellular()->dimY() - (currZ() + 1) * .5f;

    const float3 center((min_x + max_x) * .5f, (min_y + max_y) * .5f, currZ() * 2.f + .5f);
    const float half_height = 1.1f;
    const float half_width_x = (max_x - min_x + 1.f) * .5f;
    const float half_width_y = (max_y - min_y + 1.f) * .5f;
    const float thrid_length_x = (max_x - min_x) * .33f;
    const float thrid_length_y = (max_y - min_y) * .33f;

    setColor(float3(1.f, 1.f, 1.f), .66f);
    glLineWidth(1.f);

    glBegin(GL_LINES);

    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y - thrid_length_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y - thrid_length_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x - thrid_length_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x - thrid_length_x, center.y + half_width_y, center.z - half_height);

    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y - thrid_length_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y - thrid_length_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x + thrid_length_x, center.y + half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y + half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x + thrid_length_x, center.y + half_width_y, center.z - half_height);

    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y + thrid_length_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y + thrid_length_y, center.z - half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x + thrid_length_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x - half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x - half_width_x + thrid_length_x, center.y - half_width_y, center.z - half_height);

    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y + thrid_length_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y + thrid_length_y, center.z - half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x - thrid_length_x, center.y - half_width_y, center.z + half_height);
    glVertex3f(center.x + half_width_x, center.y - half_width_y, center.z - half_height);
    glVertex3f(center.x + half_width_x - thrid_length_x, center.y - half_width_y, center.z - half_height);

    glEnd();

}

void RenderArea3D::setRadiusAndCenter() {
    using namespace qglviewer;

    const float3 min(-.5f, -(cellular()->dimY() + cellular()->dimZ() * .5f + 1.f), -.5f);
    const float3 max(cellular()->dimX() + cellular()->dimZ() * .5f,
                     cellular()->dimY() - .5f,
                     cellular()->dimZ() * 2 - .5f);

    setSceneBoundingBox(Vec(min.x, min.y, min.z), Vec(max.x, max.y, max.z));

    Quaternion q;
    q.setAxisAngle(Vec(4, 2, 3), 1.f);
    camera()->setOrientation(q);
//    camera()->setPosition(qglviewer::Vec(_max.x * 1.35f, _max.y * -1.4f, _max.z * 2.8f));
    showEntireScene();
}
