/*
 * Engine.h
 *
 *  Created on: Nov 30, 2013
 *      Author: Nishry
 */

#ifndef _ENGINE
#define _ENGINE

#include <jni.h>
#include <android/log.h>

#define DEBUG 1

#define LOG_TAG "ENGINE"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)

#else
#define LOGV(...)
#endif

#include "Application.h"

#endif /* ENGINE_H_ */
