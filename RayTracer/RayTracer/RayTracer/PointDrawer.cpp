#include "PointDrawer.h"

void Draw_Point(GLint x, GLint y, Color color)
{
	glColor3f(color.r, color.g, color.b);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
