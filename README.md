Ding context-related search
=========

Configurable module that allows the local admins to pre-filter/facet a searchResult.

## Configuration:
Enable module on @/admin/modules page.

## Usage:
Go to @/admin/config/ding/dcrs admin configuration form.
In URL filed enter some path (e.g. "/" if you want to use front page),
filter filed should contain facet name and value (e.g. term.type="music").
You can add such filters as many as you want.

After you configured module, it will add CQL to search keywords when you start search on URL you used.
