plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

val nativeProjectDir = projectDir.parentFile?.parentFile

android {
    namespace = "com.example.rayapp2"
    compileSdk = 33

    defaultConfig {
        applicationId = "com.example.rayapp2"
        minSdk = 21
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        // testInstrumentationRunner("androidx.test.runner.AndroidJUnitRunner")
//        externalNativeBuild {
//            cmake {
//                cppFlags "-std=c++17"
//            }
//        }


        ndk {
            abiFilters += listOf("armeabi-v7a")
        }
        vectorDrawables {
            useSupportLibrary = true
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile ("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
//    externalNativeBuild {
//        cmake {
//            path file("src/main/cpp/CMakeLists.txt")
//            version "3.22.1"
//        }
//    }
    buildFeatures {
        viewBinding = true
        compose = true
    }

    val mainSourceSet = sourceSets.named("main").get()
    composeOptions {
        kotlinCompilerExtensionVersion = "1.3.2"
    }
    packagingOptions {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }

    sourceSets {
        named("main") {
            if (nativeProjectDir != null) {
                assets.srcDir(nativeProjectDir.resolve("assets"))
            }
        }
    }

    val configureCMake by tasks.registering(Exec::class) {
        if (nativeProjectDir == null) {
            throw IllegalStateException("Cannot compile: project not found.")
        }

        val cmakeDir = nativeProjectDir.resolve("cmake-build-android")

        doFirst {
            cmakeDir.mkdir()
        }

        workingDir = cmakeDir

        executable = "cmake"
        args("..",
            "-DCMAKE_SYSTEM_NAME=Android",
            "-DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a",
            "-DCMAKE_SYSTEM_VERSION=21",
            "-DCMAKE_BUILD_TYPE=Debug",
            "-GNinja")
    }

    val buildCMake by tasks.registering(Exec::class) {
        if (nativeProjectDir == null) {
            throw IllegalStateException("Cannot compile: project not found.")
        }

        val cmakeDir = nativeProjectDir.resolve("cmake-build-android")
        assert(cmakeDir.exists())

        workingDir = cmakeDir
        executable = "cmake"
        args("--build", ".", "--target", "PastequeArena", "-j", Runtime.getRuntime().availableProcessors())

        dependsOn(configureCMake)
    }

    val copyLibraries by tasks.registering(Copy::class) {
        if (nativeProjectDir == null) {
            throw IllegalStateException("Cannot compile: project not found.")
        }

        val binary = nativeProjectDir.resolve("cmake-build-android/libPastequeArena.so")
        assert(binary.exists())

        from(binary)
        // todo: mainSourceSet.jniLibs.srcDirs.first()
        destinationDir = projectDir.resolve("src/main/jniLibs/armeabi-v7a")

        dependsOn(buildCMake)
    }

    tasks.preBuild {
        dependsOn(copyLibraries)
    }
}

dependencies {

    implementation("androidx.core:core-ktx:1.8.0")
    implementation("androidx.appcompat:appcompat:1.4.1")
    implementation("com.google.android.material:material:1.5.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.3")
    implementation("androidx.lifecycle:lifecycle-runtime-ktx:2.3.1")
    implementation("androidx.activity:activity-compose:1.5.1")
    implementation(platform("androidx.compose:compose-bom:2022.10.00"))
    implementation("androidx.compose.ui:ui")
    implementation("androidx.compose.ui:ui-graphics")
    implementation("androidx.compose.ui:ui-tooling-preview")
    implementation("androidx.compose.material3:material3")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.3")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.4.0")
    androidTestImplementation(platform("androidx.compose:compose-bom:2022.10.00"))
    androidTestImplementation("androidx.compose.ui:ui-test-junit4")
    debugImplementation("androidx.compose.ui:ui-tooling")
    debugImplementation("androidx.compose.ui:ui-test-manifest")
}