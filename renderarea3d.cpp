#include "renderarea3d.h"
#include "cellspainter3d.h"

RenderArea3D::RenderArea3D(QWidget *parent, Cellular *cellular, int area_size)
    : QGLViewer(parent), RenderAreaI(cellular), _area_size(area_size), _cell_height(.5f) {}

RenderArea3D::~RenderArea3D() {
    delete _cells_painter;
}

QSize RenderArea3D::minimumSizeHint() const {
    return QSize(width(), height());
}

void RenderArea3D::drawCell(const float3 &center, const float3 &color, float alpha) {
    primitiveCell(center, .46f, color, alpha);
}

void RenderArea3D::drawCellBorder(const float3 &center, const float3 &color, float alpha) {
    primitiveCellBorder(center, .475f, color, alpha);
}

void RenderArea3D::drawBCell(const float3 &center, const float3 &color, float alpha) {
    drawCell(center, color, alpha);
    const float coef = .8f;
    float3 darken(color.x * coef, color.y * coef, color.z * coef);
    drawCellBorder(center, darken, alpha);
}

void RenderArea3D::drawHalfDimer(const float3 &center, float alpha) {
    const float half_width = .25f;
    const float half_height = .05f;

    primitiveParallelepiped(center, float3(half_width, half_width, half_height), float3(.9f, .9f, .9f), alpha);
}

void RenderArea3D::init() {
    glDisable(GL_LIGHTING);
//    glEnable(GL_LIGHTING);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

//    float ambient[4] = {.3f, .3f, .3f, 1.f};
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_BLEND);
//    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//////    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    GLfloat gl_diff_color[] = { 1, 1, 1, 1 };
//    glMaterialfv(GL_BACK, GL_DIFFUSE, gl_diff_color);
////    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gl_diff_color);

    setRadiusAndCenter();
    _cells_painter = createVisitor();
}

void RenderArea3D::draw() {
    drawSliceSelector();
    cellular()->store(cellsPainter());
}

CellsVisitor *RenderArea3D::createVisitor() {
    return new CellsPainter3D(this, cellular()->dimY() - 1);
}

void RenderArea3D::primitiveCell(const float3 &center, float half_side_length, const float3 &color, float alpha) {
    primitiveParallelepiped(center, float3(half_side_length, half_side_length, half_side_length * _cell_height), color, alpha);
}

void RenderArea3D::primitiveCellBorder(const float3 &center, float half_side_length, const float3 &color, float alpha) {
    primitiveParallelepipedBorder(center, float3(half_side_length, half_side_length, half_side_length * _cell_height), 2.f, color, alpha);
}

void RenderArea3D::primitiveParallelepiped(const float3 &center, const float3 &half_side_lengths, const float3 &color, float alpha) {
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

void RenderArea3D::primitiveParallelepipedBorder(const float3 &center, const float3 &half_side_lengths, float border_width,
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

void RenderArea3D::resetCamera() {
    qglviewer::Quaternion q;
    q.setAxisAngle(qglviewer::Vec(4, 2, 3), 1.f);
    camera()->setOrientation(q);
    showEntireScene();
}

void RenderArea3D::drawSliceSelector() {
    const float min_x = (currZ() - 1) * .5f;
    const float max_x = cellular()->dimX() + (currZ() + 1) * .5f;

    const float min_y = -cellular()->dimY() - currZ() * .5f - 1.5f;
    const float max_y = cellular()->dimY() - (currZ() + 1) * .5f;

    const float3 center((min_x + max_x) * .5f, (min_y + max_y) * .5f, (currZ() * 2.f + .5f) * _cell_height);
    const float half_height = 1.1f * _cell_height;
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
    const float3 min(-.5f, -(cellular()->dimY() + cellular()->dimZ() * .5f + 1.f), -.5f * _cell_height);
    const float3 max(cellular()->dimX() + cellular()->dimZ() * .5f,
                     cellular()->dimY() - .5f,
                     (cellular()->dimZ() * 2 - .5f) * _cell_height);

    setSceneBoundingBox(qglviewer::Vec(min.x, min.y, min.z), qglviewer::Vec(max.x, max.y, max.z));

    resetCamera();
}
