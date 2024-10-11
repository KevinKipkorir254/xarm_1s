from setuptools import find_packages
from setuptools import setup

setup(
    name='xarm_1s_messages',
    version='0.0.0',
    packages=find_packages(
        include=('xarm_1s_messages', 'xarm_1s_messages.*')),
)
