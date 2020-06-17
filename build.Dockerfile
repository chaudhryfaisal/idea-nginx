FROM openjdk:8 AS cache
ENV BUILD=/build
WORKDIR $BUILD
COPY build.gradle gradle.properties settings.gradle gradlew $BUILD/
COPY gradle $BUILD/gradle
RUN ./gradlew build -i || return 0

FROM cache
RUN apt install git
ENV BUILD=/build
ENV GRADLE_ARGS="-i --no-daemon"
WORKDIR $BUILD
COPY vendor.sh $BUILD
ADD vendor_overrides $BUILD/vendor_overrides
RUN ./vendor.sh
#COPY . $BUILD
COPY src $BUILD/src
COPY resources $BUILD/resources
RUN GRADLE=$(find /root -name gradle -type f); $GRADLE $GRADLE_ARGS generateDocumentation ; $GRADLE $GRADLE_ARGS buildPlugin
RUN cat resources/*.txt