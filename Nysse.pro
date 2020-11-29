TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
        Game \
    statistics_test

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
