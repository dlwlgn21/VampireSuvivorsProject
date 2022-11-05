#include "yaCamera.h"
#include "yaApplication.h"
#include "yaGameObejct.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaImage.h"

namespace ya
{

	Vector2 Camera::mResolution = Vector2::ZERO;
	Vector2 Camera::mLookPosition = Vector2::ZERO;
	Vector2 Camera::mDistance = Vector2::ZERO;			// 해상도 중심좌표와 현재 카메라의 간격차이.
	GameObject* Camera::mTarget = nullptr;
	float Camera::mSpeed = 500.0f;

	eCameraEffect Camera::mEffect;
	Image* Camera::mpImageCutton = nullptr;				// 검정색 이미지
	float Camera::mAlphaTime = 0.0f;
	float Camera::mCuttonAlphaValue = 1.0f;
	float Camera::mAlphaEndTime = 3.0f;
	BLENDFUNCTION Camera::mFunc;

	void Camera::Initialize()
	{
		WindowData windowData = Application::GetInstance().GetWindowData();
		mResolution = Vector2(windowData.width, windowData.height);
		mLookPosition = mResolution / 2.0f;							// 가운데로 할거양
		//mEffect = eCameraEffect::FADE_IN;
		mpImageCutton = Image::Create(
			L"CameraCutton",
			Application::GetInstance().GetWindowData().width,
			Application::GetInstance().GetWindowData().height
		);
		assert(mpImageCutton != nullptr);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = 0;
	}
	void Camera::Tick()
	{
		if (mAlphaTime <= mAlphaEndTime)
		{
			mAlphaTime += Time::DeltaTime();

			float ratio = (mAlphaTime / mAlphaEndTime);

			if (mEffect == eCameraEffect::FADE_IN)
			{
				mCuttonAlphaValue = 1.0f - ratio;
			}
			else if (mEffect == eCameraEffect::FADE_OUT)
			{
				mCuttonAlphaValue = ratio;
			}

		}

		if (IS_KEY_PRESSED(eKeyCode::UP))
		{
			mLookPosition.y -= mSpeed * Time::DeltaTime();
		}
		if (IS_KEY_PRESSED(eKeyCode::DOWN))
		{
			mLookPosition.y += mSpeed * Time::DeltaTime();
		}
		if (IS_KEY_PRESSED(eKeyCode::LEFT))
		{
			mLookPosition.x -= mSpeed * Time::DeltaTime();
		}
		if (IS_KEY_PRESSED(eKeyCode::RIGHT))
		{
			mLookPosition.x += mSpeed * Time::DeltaTime();
		}

		if (mTarget != nullptr) { mLookPosition = mTarget->GetPos(); }


		mDistance = mLookPosition - (mResolution / 2.0f);
	}
	void Camera::Render(HDC hdc)
	{
		if (mCuttonAlphaValue <= 0.0f)
		{
			return;
		}
		mFunc.SourceConstantAlpha = static_cast<BYTE>(255.0f * mCuttonAlphaValue);
		AlphaBlend(
			hdc,
			static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(mpImageCutton->GetWidth()),
			static_cast<int>(mpImageCutton->GetHeight()),

			mpImageCutton->GetDC(),
			0, 0,
			mpImageCutton->GetWidth(),
			mpImageCutton->GetHeight(),
			mFunc
		);

	}
}