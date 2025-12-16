# 🗑️ Simple Garbage Collector for C

A tiny automatic-cleanup system built on top of `malloc()`.

This project implements a lightweight “garbage collector” for C using a linked list to track allocated memory.
All allocations are automatically freed when requested, helping prevent memory leaks in larger projects.

---

## 🚀 Features

* ✔️ Simple wrapper around `malloc()`
* ✔️ Tracks every allocated pointer
* ✔️ Frees **all** tracked allocations with a single call
* ✔️ Automatically cleans after allocation errors
* ✔️ Drop-in replacement for `malloc()` in many cases
* ✔️ No external dependencies (uses your own `libft` linked-list utilities)

---

## 📌 How It Works

All allocations go through:

```c
void *ft_malloc(size_t size, bool CLEAN);
```

Internally:

* A **static linked list** stores every returned pointer.
* On each successful allocation, the pointer is pushed into the list.
* When `CLEAN` is set to `true`, the function:

  * Frees every pointer stored in the list
  * Clears the list
  * Returns `NULL`

This allows a single call to wipe all allocated memory—very helpful for error handling.

---

## 🧠 Example Usage

### Basic allocation

```c
char *str = ft_malloc(50, false);
if (!str)
    return (1);

strcpy(str, "Hello world!");
printf("%s\n", str);
```

### Free all allocations at once

```c
ft_malloc(0, true); // triggers full cleanup
```

### Using during parsing or multi-step logic

```c
char *a = ft_malloc(10, false);
char *b = ft_malloc(20, false);
char *c = ft_malloc(30, false);

if (!a || !b || !c)
    return (ft_malloc(0, true), 1); // clean and exit

// ... program logic ...

// Final cleanup
ft_malloc(0, true);
```

---

## 🧼 Cleaning Function

```c
void cleaning(t_list **lis)
{
    ft_lstclear(lis, free);
    *lis = NULL;
}
```

This function is automatically called inside `ft_malloc()` on cleanup or failure.

---

## 📂 Integration

Include the header containing `ft_malloc()` and ensure your project has:

* `ft_lstnew()`
* `ft_lstadd_back()`
* `ft_lstclear()`
* `t_list` structure

These are commonly found in a standard 42-style `libft`.

---

## ⚠️ Limitations & Notes

* ❗ This is **not a true garbage collector**
  (you must manually call cleanup once you're done)
* ❗ All allocated blocks are freed **together**
  (no per-pointer free function)
* ⚠️ Thread-unsafe due to static storage (fixable by using mutex or specific var type)
* ⚠️ If you store pointers allocated outside `ft_malloc()`, they **won’t** be tracked
* ⚠️ Don't use free on stored memory, for avoiding duble frees 
* 👌 Ideal for parsing, shell projects, game loops, or large chained operations

---

## 📜 License

MIT License — free to use, modify, and distribute.
