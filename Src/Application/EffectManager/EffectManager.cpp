#include"Application/Headers.h"

EffectManager::~EffectManager()
{
    // マネージャーの破棄
    m_manager.Reset();

    // レンダラーの破棄
    m_renderer.Reset();

    m_effectList.clear();
}

void EffectManager::Init()
{
    //===================================================================
    // エフェクシア
    //===================================================================
    ID3D11Device* d3D11Device = D3D.GetDev();
    ID3D11DeviceContext* d3D11DeviceContext = D3D.GetDevContext();

    //D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &d3D11Device, nullptr, &d3D11DeviceContext);
    m_renderer = ::EffekseerRendererDX11::Renderer::Create(d3D11Device, d3D11DeviceContext, 8000);

    // エフェクトのマネージャーの作成
    m_manager = ::Effekseer::Manager::Create(8000);

    // 描画モジュールの設定
    m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
    m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
    m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
    m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
    m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

    // テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
    // ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
    m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
    m_manager->SetModelLoader(m_renderer->CreateModelLoader());
    m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
    m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

    auto g_position = ::Effekseer::Vector3D(0, 0, 20.0f);

    // 投影行列を設定
    m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovRH(
    90.0f / 180.0f * 3.14f, 1280.0f / 720.0f, 1.0f, 500.0f));

    // カメラ行列を設定
    m_renderer->SetCameraMatrix(
        ::Effekseer::Matrix44().LookAtRH(g_position, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}

const EffekseerRendererDX11::RendererRef& EffectManager::GetRenderer() const
{
    return m_renderer;
}

const Effekseer::ManagerRef& EffectManager::GetManager() const
{
    return m_manager;
}

const std::shared_ptr<Effekseer::EffectRef> EffectManager::GetEffect(const std::string _fileName, const char16_t* _effect)
{
    std::shared_ptr<Effekseer::EffectRef> tmpEffect = nullptr;

    if (m_effectList.find(_fileName) == m_effectList.end())
    {
        //初めて読み込まれていたら
        tmpEffect   = std::make_shared<Effekseer::EffectRef>();
        *tmpEffect  = Effekseer::Effect::Create(EFFEKSEER.GetManager(), _effect);

        m_effectList[_fileName] = tmpEffect;
    }
    else
    {
        //すでに読み込まれていたら 
        tmpEffect = m_effectList[_fileName];
    }

    return tmpEffect;
}
