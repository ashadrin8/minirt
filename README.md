*This project has been created as part of the 42 curriculum by [ashadrin, ckappe].*

# miniRT

## Description
`miniRT` is a small ray tracer written in C with the MiniLibX 42 graphics library (MLX42).
The goal is to read a scene from a `.rt` file, cast one ray per pixel from the camera, find the closest object hit, and compute the final pixel color using ambient + diffuse lighting and hard shadows.

This project currently supports:
- Scene elements: ambient light (`A`), camera (`C`), light (`L`)
- Objects: sphere (`sp`), plane (`pl`), cylinder (`cy`), cone (`co`)
- Camera controls with keyboard arrows (rotation)
- Window resize re-rendering

## Instructions
### Build
```bash
make
```
### Run
```bash
./miniRT minimalistic.rt
```
### Extra
```bash
./miniRT tests/room1.rt      # other provided scenes
make re                       # rebuild from scratch
```

### Notes on dependencies
The project builds MLX42 through CMake from the `MLX42` submodule and links with `glfw`, `pthread`, `dl`, and `m`.
Depending on your OS, you may need to install system packages for GLFW/CMake before `make` succeeds.

### Controls
- `ESC`: close window
- `Arrow Up/Down`: pitch camera
- `Arrow Left/Right`: turn camera

## Code Flow (High-Level)

### 1. Program entry
- `minirt.c`: `main()` initializes `t_scene`, parses the `.rt` file, opens the window, renders, then frees scene memory.

### 2. Parsing stage
- `src/parsing/parsing.c`: `validate_and_parse()` checks arguments, validates `.rt`, reads file line by line, and dispatches each line to the correct parser.
- `src/parsing/parse_scene_settings.c` and `src/parsing/parse_objects.c`: validate values and store scene/camera/light/object data.
- `src/parsing/initialization.c`: creates and appends linked-list nodes for objects.

### 3. Render loop
- `src/render/window.c`: creates MLX window/image, installs hooks, triggers rendering.
- `src/render/render_scene.c`: loops over all pixels.
  - Build primary ray (`ray_create`)
  - Find closest object hit (`hit_closest_*`)
  - Shade hit (`shade_hit`) or paint black for miss

### 4. Intersection layer
- `src/objects/sphere.c`: analytic quadratic sphere intersection
- `src/objects/plane.c`: plane-ray intersection
- `src/objects/cylinder*.c`: cylinder side + caps
- `src/objects/cone*.c`: cone side + base

### 5. Lighting and shadows
- `src/render/light.c`: ambient + Lambert diffuse
- `src/render/shadow.c`: shadow ray toward light, with bias (`EPS`) and self-shadow skipping

## Math Notes (How the Rendering Works)

### 1. Ray equation
A ray is represented as:
- `P(t) = O + tD`
- `O`: ray origin (camera position)
- `D`: normalized direction
- `t > 0`: distance along the ray

### 2. Camera basis and image plane
The camera computes an orthonormal basis:
- `forward`: viewing direction
- `right = normalize(cross(forward, world_up))`
- `up = normalize(cross(forward, right))`

From POV and aspect ratio, the code computes the virtual view-plane width/height and its lower-left corner. Each pixel maps to `(u, v)` on this plane, producing one ray direction.

### 3. Sphere intersection
For sphere center `C` and radius `r`, substitute ray equation into:
- `|P(t) - C|^2 = r^2`
This gives a quadratic in `t`. If discriminant `< 0`, no hit. Otherwise the smallest positive root is chosen.
In simple terms: we check where the ray enters/exits the sphere shell and keep the first valid point in front of the camera.

### 4. Plane intersection
For plane point `P0` and normal `N`, solve:
- `t = dot(P0 - O, N) / dot(D, N)`
If denominator is near zero, the ray is parallel to the plane.
In simple terms: we project the ray onto the plane normal to get the distance to the infinite flat surface.

### 5. Cylinder and cone intersections
The implementation uses object axis projection:
- Split vectors into components parallel/perpendicular to axis
- Solve quadratic for side surface
- Validate finite height bounds
- Separately test end caps (cylinder) or base disk (cone)
- Keep nearest valid positive `t`

For a finite cylinder side, the code first intersects the infinite tube, then rejects hits outside the allowed height.  
For cylinder caps, each cap is treated as a plane disk: intersect ray with cap plane, then check if hit point is inside cap radius.  
For cones, side hits are also solved with a quadratic, then filtered by height from apex to base.  
For cone base, it uses the same disk idea as a cylinder cap (plane hit + radius check).

### 6. Numerical constants (`INF` and `EPS`)
- `INF` is a very large sentinel distance used as the initial "no hit yet" value when searching for the closest intersection.
- `EPS` is a tiny positive threshold used to avoid floating-point artifacts (self-intersections, near-zero denominators, and shadow acne).
- In practice, hits with `t <= EPS` are ignored, and shadow rays start with a small normal-based offset (`EPS` bias).

### 7. Shading model
At hit point:
- Ambient: `base_color * ambient_ratio`
- Diffuse (Lambert): `base_color * max(0, dot(N, L)) * light_brightness`
- Final: `clamp(ambient + diffuse)`

If a shadow ray hits another object before the light, only ambient is used.

## Project Structure
```text
includes/
minirt.c
src/
  parsing/
  render/
  objects/
  vector_math/
tests/
MLX42/
libft/
```

## Resources
Classic references used for ray tracing and implementation checks:
- 42 miniRT subject (intra/project statement)
- Scratchapixel: Rendering and ray-object intersection basics  
  https://www.scratchapixel.com/
- Ray Tracing in One Weekend (book series)  
  https://raytracing.github.io/
- PBRT (Physically Based Rendering, online book)  
  https://pbr-book.org/
- LearnOpenGL math refresher (vectors, dot/cross products)  
  https://learnopengl.com/
- C math functions reference (`sqrt`, `tan`, etc.)  
  https://en.cppreference.com/w/c/numeric/math

### AI usage
AI assistance was used for:
- Structuring the README documentation
- Clarifying math explanations (camera basis, intersections, shading)
- Reviewing edge-case reasoning (EPS bias, root selection, self-shadow handling)

AI was not used as a substitute for manual coding decisions, compilation, testing, or understanding project requirements.
