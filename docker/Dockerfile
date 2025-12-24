# Base image with Intel VTune
FROM intel/oneapi-vtune:2025.2.4-0-devel-ubuntu22.04

RUN apt update && apt upgrade -y
# Install build tools and performance utilities
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    gdb \
    make \
    cmake \
    numactl \
    linux-tools-common \
    linux-tools-generic \
    linux-tools-6.8.0-87-generic \
    valgrind
# Workaround for missing perf in 6.14.
RUN ln -s /usr/lib/linux-tools/6.8.0-87-generic/perf /usr/sbin/perf

# Default shell
CMD ["/bin/bash"]
