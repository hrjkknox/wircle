from distutils.core import setup, Extension

setup(
    ext_modules=[
		Extension(
			name="wircle",
            sources=["src/wircle/wirclemodule.c"]
		)
	]
)
