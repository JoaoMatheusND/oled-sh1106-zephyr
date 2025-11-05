# oled-sh1106-zephyr

### Dependencies

This module is dependent on OLED fonts, available at https://github.com/edgebr/oled-mono-fonts/tree/zephyr as a module
as well. The final `west.yml` will look like:

```yaml
      [...]
    - name: oled-mono-fonts
      remote: edgebr # or url to the mentioned repo, if remote is not set.
      revision: zephyr
      
    - name: oled-sh1106-zephyr
      remote: edgebr # or url to this repo, if remote is not set.
      revision: zephyr
      clone-depth: 1
      path: deps/display
```
