TEMPLATE = subdirs
QT += testlib
SUBDIRS += \
	CourseLib \
	Game

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
