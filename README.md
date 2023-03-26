# wircle

A library for creating wavy circles

## Functions

### `getPoint(radius, amplitude, angle, count, centre) -> (float, float)`

Get a single point on the wircle at a defined angle for the given values.

- `radius: float`: The radius of the wircle
- `amplitude: float`: The amplitude of the wircle
- `angle: float`: The angle on the wircle that the point is located at (in radians)
- `count: integer`: The number of waves on the wircle
- `centre: (float, float)`: The centre point of the wircle

### `getPoints(radius, amplitude, count, centre, resolution) -> [(float, float),  ...]`

Get a list of points on the wircle

- `radius: float`: The radius of the wircle
- `amplitude: float`: The amplitude of the wircle
- `count: integer`: The number of waves on the wircle
- `centre: (float, float)`: The centre point of the wircle
- `resolution: integer`: The resolution of the wircle (i.e. how many points there are)
