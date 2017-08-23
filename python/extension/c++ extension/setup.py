from distutils.core import setup, Extension

MOD = 'vector'
setup(name=MOD, ext_modules=[Extension(MOD, sources=['vector.c'])])
