package com.example.opengles_android;


import android.opengl.GLES20;
import android.opengl.Matrix;
import android.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

public class ExposureFilter {
    public final Object mMBCExposureFilter = new Object();
    private static final String EXPOSURE_TAG = "MBCExposureFilter";
    private final String mVertexShaderCode = "///////////////////////////////////////////////////////////\n" +
            "//attribute\n" +
            "attribute vec4 a_position;\n" +
            "attribute vec2 a_texCoord;\n" +
            "///////////////////////////////////////////////////////////\n" +
            "//uniform\n" +
            "uniform mat4 u_modelMatrix;\n" +
            "uniform mat4 u_viewMatrix;\n" +
            "uniform mat4 u_projectionMatrix;\n" +
            "\n" +
            "///////////////////////////////////////////////////////////\n" +
            "//varying\n" +
            "varying vec2 v_texCoord;\n" +
            "\n" +
            "\n" +
            "void main(void) {\n" +
            "\tv_texCoord = a_texCoord;\n" +
            "    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;\n" +
            "}\n" +
            "\n";

    private final String mFragmentShaderCode = "#ifdef GL_ES//for discriminate GLES & GL\n" +
            "#ifdef GL_FRAGMENT_PRECISION_HIGH\n" +
            "precision highp float;\n" +
            "#else\n" +
            "precision mediump float;\n" +
            "#endif\n" +
            "#else\n" +
            "#define highp\n" +
            "#define mediump\n" +
            "#define lowp\n" +
            "#endif\n" +
            "\n" +
            "\n" +
            "///////////////////////////////////////////////////////////\n" +
            "//uniform\n" +
            "uniform sampler2D u_texture;\n" +
            "uniform float u_exposure;\n" +
            "///////////////////////////////////////////////////////////\n" +
            "//varying\n" +
            "varying vec2 v_texCoord;\n" +
            "\n" +
            "void main() {\n" +
            "\thighp vec4 texture = texture2D(u_texture, v_texCoord);\n" +
            "\tgl_FragColor = vec4(texture.rgb * pow(2.0, u_exposure), texture.a);\n" +
            "}\n";

    private final FloatBuffer mVertexVbo;
    private final FloatBuffer mTexCoordVbo;
    private final ShortBuffer mEbo;
    private final int mProgram;
    private int mPositionHandle;
    private int mTexCoordHandle;
    private int mModelMatrixHandle;
    private int mViewMatrixHandle;
    private int mProjectionMatrixHandle;
    private int mExposureAlphaHandle;
    private int mTextureHandle;
    private final float[] mModelMatrix = new float[16];
    private final float[] mProjectionMatrix = new float[16];
    private final float[] mViewMatrix = new float[16];
    static final int COORDS_PER_VERTEX = 4;
    static final int COORDS_PER_TEXCOORD = 2;
    static final float vertices[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,   // bottom left
            1.0f, -1.0f, 0.0f, 1.0f,   // bottom right
            -1.0f,  1.0f, 0.0f, 1.0f,   // top left
            1.0f,  1.0f, 0.0f, 1.0f,   // top right
    };
    static final float texCoords[] = {
            0.0f, 0.0f,   // bottom left
            1.0f, 0.0f,   // bottom right
            0.0f, 1.0f,   // top left
            1.0f, 1.0f    // top right
    };
    static final short indexes[] = {
            0, 1, 2, 2, 1, 3
    };
    private final int vertexStride = COORDS_PER_VERTEX * 4; // 4 bytes per vertex
    private final int texCoordStride = COORDS_PER_TEXCOORD * 4;
    ExposureFilter() {
        ByteBuffer vertexVboByteBuffer = ByteBuffer.allocateDirect(vertices.length * 4);
        vertexVboByteBuffer.order(ByteOrder.nativeOrder());
        mVertexVbo = vertexVboByteBuffer.asFloatBuffer();
        mVertexVbo.put(vertices);
        mVertexVbo.position(0);

        ByteBuffer texCoordVboByteBuffer = ByteBuffer.allocateDirect(texCoords.length * 4);
        texCoordVboByteBuffer.order(ByteOrder.nativeOrder());
        mTexCoordVbo = texCoordVboByteBuffer.asFloatBuffer();
        mTexCoordVbo.put(texCoords);
        mTexCoordVbo.position(0);

        ByteBuffer eboByteBuffer = ByteBuffer.allocateDirect(indexes.length * 2);
        eboByteBuffer.order(ByteOrder.nativeOrder());
        mEbo = eboByteBuffer.asShortBuffer();
        mEbo.put(indexes);
        mEbo.position(0);

        int vertShader = ExposureFilter.loadShader(GLES20.GL_VERTEX_SHADER, mVertexShaderCode);
        int fragShader = ExposureFilter.loadShader(GLES20.GL_FRAGMENT_SHADER, mFragmentShaderCode);
        mProgram = ExposureFilter.createProgram(vertShader, fragShader);
        Matrix.setIdentityM(mModelMatrix, 0);
        Matrix.setLookAtM(mViewMatrix, 0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        Matrix.orthoM(mProjectionMatrix, 0, -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        mPositionHandle = GLES20.glGetAttribLocation(mProgram, "a_position");
        mTexCoordHandle = GLES20.glGetAttribLocation(mProgram, "a_texCoord");
        ExposureFilter.checkGlError("glGetAttribLocation");
        mModelMatrixHandle = GLES20.glGetUniformLocation(mProgram, "u_modelMatrix");
        mViewMatrixHandle = GLES20.glGetUniformLocation(mProgram, "u_viewMatrix");
        mProjectionMatrixHandle = GLES20.glGetUniformLocation(mProgram, "u_projectionMatrix");
        mExposureAlphaHandle = GLES20.glGetUniformLocation(mProgram, "u_exposure");
        mTextureHandle = GLES20.glGetUniformLocation(mProgram, "u_texture");
        ExposureFilter.checkGlError("glGetUniformLocation");
    }

    public int drawTexAToFboB(int fboIn, int texIn, int fboOut, int texOut, int nTexWidth, int nTexHeight) {
        synchronized (mMBCExposureFilter) {
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, fboOut);
            GLES20.glClearColor(0.0f,1.f,1.0f, 1.0f);
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
            GLES20.glUseProgram(mProgram);
            GLES20.glEnableVertexAttribArray(mPositionHandle);
            GLES20.glVertexAttribPointer(mPositionHandle, 4, GLES20.GL_FLOAT, false, vertexStride, mVertexVbo);
            GLES20.glEnableVertexAttribArray(mTexCoordHandle);
            GLES20.glVertexAttribPointer(mTexCoordHandle, 2, GLES20.GL_FLOAT, false, texCoordStride, mTexCoordVbo);
            GLES20.glUniformMatrix4fv(mModelMatrixHandle, 1, false, mModelMatrix,0);
            GLES20.glUniformMatrix4fv(mViewMatrixHandle, 1, false, mViewMatrix,0);
            GLES20.glUniformMatrix4fv(mProjectionMatrixHandle, 1, false, mProjectionMatrix,0);
            GLES20.glUniform1f(mExposureAlphaHandle, 0.85f);
            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texIn);
            GLES20.glUniform1i(mTextureHandle, 0);
            GLES20.glDrawElements(GLES20.GL_TRIANGLE_STRIP, indexes.length, GLES20.GL_UNSIGNED_SHORT, mEbo);
            GLES20.glDisableVertexAttribArray(mPositionHandle);
            GLES20.glDisableVertexAttribArray(mTexCoordHandle);
            GLES20.glUseProgram(0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
            return texOut;
        }
    }

    private static int createProgram(int vertShader, int fragShader) {
        int program = GLES20.glCreateProgram();
        if (program == 0) {
            Log.e(EXPOSURE_TAG, "create program failed");
        }
        GLES20.glAttachShader(program, vertShader);
        GLES20.glAttachShader(program, fragShader);
        GLES20.glLinkProgram(program);
        int[] linked = new int[1];
        GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linked, 0);
        if (linked[0] == GLES20.GL_FALSE) {
            Log.e(EXPOSURE_TAG, "Could not link program:" + GLES20.glGetProgramInfoLog(program));
            GLES20.glDeleteShader(program);
            program = 0;
        }
        return program;
    }


    private static int loadShader(int type, String shaderCode){
        int shader = GLES20.glCreateShader(type);
        if (shader == 0) {
            Log.e(EXPOSURE_TAG, "create" + type + " shader failed");
            return 0;
        }
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);
        int[] compiled = new int[1];
        GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiled, 0);
        if (compiled[0] == GLES20.GL_FALSE) {
            Log.e(EXPOSURE_TAG, "Could not compile shader:" + type + ":" + GLES20.glGetShaderInfoLog(shader));
            GLES20.glDeleteShader(shader);
            shader = 0;
        }
        return shader;
    }

    private static void checkGlError(String glOperation) {
        int error;
        String errorStr = "";
        while ((error = GLES20.glGetError()) != GLES20.GL_NO_ERROR) {
            switch (error) {
                case GLES20.GL_INVALID_ENUM:
                    errorStr = "INVALID_ENUM";
                    break;
                case GLES20.GL_INVALID_VALUE:
                    errorStr = "INVALID_VALUE";
                    break;
                case GLES20.GL_INVALID_OPERATION:
                    errorStr = "INVALID_OPERATION";
                    break;
                case GLES20.GL_OUT_OF_MEMORY:
                    errorStr = "OUT_OF_MEMORY";
                    break;
                case GLES20.GL_INVALID_FRAMEBUFFER_OPERATION:
                    errorStr = "INVALID_FRAMEBUFFER_OPERATION";
                    break;
            }
            Log.e(EXPOSURE_TAG, glOperation + ": glError " + errorStr);
            throw new RuntimeException(glOperation + ": glError " + error);
        }
    }

}

