/*
Copyright 2016 BitTorrent Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "interlock.h"

#ifdef __APPLE__

#include <libkern/OSAtomic.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

OSSpinLock g_interlocked_spin;

#pragma GCC diagnostic pop

#elif !USE_GLIBCXX_ATOMIC_BUILTINS && !defined _WIN32

#include <pthread.h>
pthread_mutex_t g_interlocked_mutex = PTHREAD_MUTEX_INITIALIZER;

#endif // !USE_GLIBCXX_ATOMIC_BUILTINS

