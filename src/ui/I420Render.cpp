#include "I420Render.h"

// 顶点着色器
static const QString s_vertShader = R"(
    attribute vec3 vertexIn;    // xyz顶点坐标
    attribute vec2 textureIn;   // xy纹理坐标
    varying vec2 textureOut;    // 传递给片段着色器的纹理坐标
    void main(void)
    {
        gl_Position = vec4(vertexIn, 1.0);  // 1.0表示vertexIn是一个顶点位置
        textureOut = textureIn; // 纹理坐标直接传递给片段着色器
    }
)";

// 片段着色器
static QString s_fragShader = R"(
    varying vec2 textureOut;        // 由顶点着色器传递过来的纹理坐标
    uniform sampler2D textureY;     // uniform 纹理单元，利用纹理单元可以使用多个纹理
    uniform sampler2D textureU;     // sampler2D是2D采样器
    uniform sampler2D textureV;     // 声明yuv三个纹理单元
    void main(void)
    {
        vec3 yuv;
        vec3 rgb;

        // SDL2 BT709_SHADER_CONSTANTS
        // https://github.com/spurious/SDL-mirror/blob/4ddd4c445aa059bb127e101b74a8c5b59257fbe2/src/render/opengl/SDL_shaders_gl.c#L102
        const vec3 Rcoeff = vec3(1.1644,  0.000,  1.7927);
        const vec3 Gcoeff = vec3(1.1644, -0.2132, -0.5329);
        const vec3 Bcoeff = vec3(1.1644,  2.1124,  0.000);

        // 根据指定的纹理textureY和坐标textureOut来采样
        yuv.x = texture2D(textureY, textureOut).r;
        yuv.y = texture2D(textureU, textureOut).r - 0.5;
        yuv.z = texture2D(textureV, textureOut).r - 0.5;

        // 采样完转为rgb
        // 减少一些亮度
        yuv.x = yuv.x - 0.0625;
        rgb.r = dot(yuv, Rcoeff);
        rgb.g = dot(yuv, Gcoeff);
        rgb.b = dot(yuv, Bcoeff);
        // 输出颜色值
        gl_FragColor = vec4(rgb, 1.0);
    }
)";

I420Render::I420Render()
{
    mTexY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    mTexY->setFormat(QOpenGLTexture::LuminanceFormat);
    mTexY->setMinificationFilter(QOpenGLTexture::Nearest);
    mTexY->setMagnificationFilter(QOpenGLTexture::Nearest);
    mTexY->setWrapMode(QOpenGLTexture::ClampToEdge);

    mTexU = new QOpenGLTexture(QOpenGLTexture::Target2D);
    mTexU->setFormat(QOpenGLTexture::LuminanceFormat);
    mTexU->setMinificationFilter(QOpenGLTexture::Nearest);
    mTexU->setMagnificationFilter(QOpenGLTexture::Nearest);
    mTexU->setWrapMode(QOpenGLTexture::ClampToEdge);

    mTexV = new QOpenGLTexture(QOpenGLTexture::Target2D);
    mTexV->setFormat(QOpenGLTexture::LuminanceFormat);
    mTexV->setMinificationFilter(QOpenGLTexture::Nearest);
    mTexV->setMagnificationFilter(QOpenGLTexture::Nearest);
    mTexV->setWrapMode(QOpenGLTexture::ClampToEdge);
}

I420Render::~I420Render()
{}

void I420Render::init()
{
    initializeOpenGLFunctions();


    m_program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,s_vertShader);
    m_program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,s_fragShader);
    m_program.bindAttributeLocation("vertexIn",0);
    m_program.bindAttributeLocation("textureIn",1);
    m_program.link();
    m_program.bind();

    vertices << QVector2D(-1.0f,1.0f)
             << QVector2D(1.0f,1.0f)
             << QVector2D(1.0f,-1.0f)
             << QVector2D(-1.0f,-1.0f);

    textures << QVector2D(0.0f,1.f)
             << QVector2D(1.0f,1.0f)
             << QVector2D(1.0f,0.0f)
             << QVector2D(0.0f,0.0f);
}

void I420Render::updateTextureInfo(int w, int h)
{
    mTexY->setSize(w,h);
    mTexY->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);

    mTexU->setSize(w/2,h/2);
    mTexU->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);

    mTexV->setSize(w/2,h/2);
    mTexV->allocateStorage(QOpenGLTexture::Red,QOpenGLTexture::UInt8);

    mTextureAlloced=true;
}

void I420Render::updateTextureData(const YUVData &data)
{
    if(data.Y.size()<=0 || data.U.size()<=0 || data.V.size()<=0) return;

    QOpenGLPixelTransferOptions options;
    options.setImageHeight(data.height);

    options.setRowLength(data.yLineSize);
    mTexY->setData(QOpenGLTexture::Luminance,QOpenGLTexture::UInt8,data.Y.data(),&options);

    options.setRowLength(data.uLineSize);
    mTexU->setData(QOpenGLTexture::Luminance,QOpenGLTexture::UInt8,data.U.data(),&options);

    options.setRowLength(data.vLineSize);
    mTexV->setData(QOpenGLTexture::Luminance,QOpenGLTexture::UInt8,data.V.data(),&options);
}

void I420Render::paint()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    if(!mTextureAlloced) return;

    m_program.bind();
    m_program.enableAttributeArray("vertexIn");
    m_program.setAttributeArray("vertexIn",vertices.constData());
    m_program.enableAttributeArray("textureIn");
    m_program.setAttributeArray("textureIn",textures.constData());

    glActiveTexture(GL_TEXTURE0);
    mTexY->bind();

    glActiveTexture(GL_TEXTURE1);
    mTexU->bind();

    glActiveTexture(GL_TEXTURE2);
    mTexV->bind();

    m_program.setUniformValue("textureY",0);
    m_program.setUniformValue("textureU",1);
    m_program.setUniformValue("textureV",2);
    glDrawArrays(GL_QUADS,0,4);
    m_program.disableAttributeArray("vertexIn");
    m_program.disableAttributeArray("textureIn");
    m_program.release();
}

void I420Render::resize(int w,int h)
{
    glViewport(0,0,w,h);
}
