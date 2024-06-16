#ifndef TASK_H
#define TASK_H

template <class T>
T *IsSortedUntil(T *first, T *last) {
  if (first == last) {
    return last;
  }

  for (T *current = first + 1; current != last; ++current) {
    if (*current < *(current - 1)) {
      return current;
    }
  }
  return last;
}

#endif