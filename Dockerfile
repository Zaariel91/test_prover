FROM ciimage/python:3.9 as base_image

COPY install_deps.sh /app/
RUN /app/install_deps.sh

COPY docker_common_deps.sh /app/
WORKDIR /app/
RUN ./docker_common_deps.sh
RUN chown -R starkware:starkware /app

COPY WORKSPACE /app/
COPY .bazelrc /app/
COPY src /app/src
COPY bazel_utils /app/bazel_utils

# Build.
RUN bazel build //...

FROM debian:stable-slim as target

COPY --from=base_image /app/build/bazelbin/src/starkware/main/cpu/cpu_air_prover /usr/bin/
COPY --from=base_image /app/build/bazelbin/src/starkware/main/cpu/cpu_air_verifier /usr/bin/

RUN apt update && apt install -y libdw1

ENTRYPOINT [ "cpu_air_prover" ]

