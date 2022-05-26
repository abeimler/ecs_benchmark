## base image
FROM abeimler/simple-cppbuilder:latest as base

# Install packages available from standard repos
RUN pacman -Syu --noconfirm && pacman-db-upgrade && \
    pacman -S --noconfirm  \
        mesa glu libx11 libxrender libxext libxcursor libxrandr libxinerama libxi xorg-server-devel \
        alsa-lib alsa-utils alsa-oss 

FROM abeimler/simple-cppbuilder:x64-mingw-w64 as windows-base
RUN pacman -Syuu --noconfirm


## build stage
FROM base as build
COPY . .
RUN ./pre-configure.sh
CMD ["./docker-build.sh"]

## test stage
FROM build as test
CMD ["./docker-test.sh"]


FROM windows-base as build-windows
COPY . .
CMD ["./docker-build.sh"]

