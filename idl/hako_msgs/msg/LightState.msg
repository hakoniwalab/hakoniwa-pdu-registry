# One light's state now (hakoniwa-scenario-pro memo 016). Written only by the light's controller.
# source: the LightSource name (its static definition is read from JSON at start-up)
# mode: 0 off, 1 on, 2 flashing (a visible blink, e.g. an indicator)
# luminous_intensity_scale: factor on the source's photometry (1.0 = as defined)
# is_lit: whether it is lit at this instant (also decided while flashing)
string source
uint8 mode
float64 luminous_intensity_scale
bool is_lit
