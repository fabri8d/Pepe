# load_env.py
import os

Import("env")

env_path = os.path.join(env['PROJECT_DIR'], '.env')
if os.path.exists(env_path):
    defines = []
    with open(env_path) as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith('#'):
                key, value = line.split('=', 1)
                key   = key.strip()
                value = value.strip()
                os.environ[key] = value
                try:
                    int(value)
                    defines.append((key, value))
                except ValueError:
                    defines.append((key, '\\"%s\\"' % value))
    env.Append(CPPDEFINES=defines)