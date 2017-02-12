# Some examples of my Drupal modules

Full disclosure: There are some practices in there that wouldn't pass my current code reviews, such as:

- 'foreach' instances that could easily be replaced with less expensive functions like array_map, array_walk, array_filter, etc.
- long javascript strings that are better suited for inclusion in a separate file, or at the very least Heredoc.
- single functions that should have been split into more - and in many cases readability & extendability would have been improved had the functionality been part of a class.
- other better-use-of-php or drupal things such as sprintf instead of concatenation, ternary statements instead of ifs, using drupal's db request object instead of db_query, drupal's element_children function to extract config elements from form state arrays, etc.

Even with the above - this should help demonstrate the level of complexity I'm comfortable with, and perhaps some nice reusable components.
