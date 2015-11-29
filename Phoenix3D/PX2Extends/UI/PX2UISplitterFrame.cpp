// PX2UISplitterFrame.cpp

#include "PX2UISplitterFrame.hpp"
#include "PX2UICanvas.hpp"
#include "PX2InputManager.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UIAuiBlockFrame.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UISplitterFrame);
PX2_IMPLEMENT_STREAM(UISplitterFrame);
PX2_IMPLEMENT_FACTORY(UISplitterFrame);

//----------------------------------------------------------------------------
UISplitterFrame::UISplitterFrame(bool hor) :
mIsHor(hor),
mLinkFrame0(0),
mLinkFrame1(0),
mIsLinkFrameChanged(true),
mIsDragable(true),
mIsDraging(false)
{
	float size = PX2_UISM.Size_Splitter;

	SetSize(size, size);

	SetAnchorHor(Float2(0.0f, 0.0f));
	SetAnchorVer(Float2(0.0f, 0.0f));

	if (mIsHor)
	{
		SetAnchorParamHor(Float2(20.0f, 20.0f));
	}
	else
	{
		SetAnchorParamVer(Float2(20.0f, 20.0f));
	}

	ComeInEventWorld();

	UIPicBox *picBoxBottom = CreateAddBackgroundPicBox();
	picBoxBottom->SetTexture("Data/engine/white.png");
	picBoxBottom->SetColor(PX2_UISM.Color_Splitter);
}
//----------------------------------------------------------------------------
UISplitterFrame::~UISplitterFrame()
{
}
//----------------------------------------------------------------------------
void UISplitterFrame::SetLinkFrame0(UISplitterFrame *frame)
{
	if (mLinkFrame0)
	{
		mLinkFrame0->RemoveLinkMeSpFrame(this);
	}

	mLinkFrame0 = frame;

	if (mLinkFrame0)
	{
		mLinkFrame0->AddLinkMeSpFrame(this);
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::SetLinkFrame1(UISplitterFrame *frame)
{
	if (mLinkFrame1)
	{
		mLinkFrame1->RemoveLinkMeSpFrame(this);
	}

	mLinkFrame1 = frame;

	if (mLinkFrame1)
	{
		mLinkFrame1->AddLinkMeSpFrame(this);
	}
}
//----------------------------------------------------------------------------
bool UISplitterFrame::IsHasLinkMeSpFrame(UISplitterFrame *frame)
{
	for (int i=0; i<(int)mLinkMeSpFrames.size(); i++)
	{
		if (frame == mLinkMeSpFrames[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UISplitterFrame::AddLinkMeSpFrame(UISplitterFrame *frame)
{
	if (IsHasLinkMeSpFrame(frame))
		return;

	mLinkMeSpFrames.push_back(frame);
}
//----------------------------------------------------------------------------
void UISplitterFrame::RemoveLinkMeSpFrame(UISplitterFrame *frame)
{
	std::vector<UISplitterFrame*>::iterator it = mLinkMeSpFrames.begin();
	for(; it!=mLinkMeSpFrames.end(); it++)
	{
		if (*it == frame)
		{
			mLinkMeSpFrames.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::_MarkLinkMeFramesChange()
{
	for (int i=0; i<(int)mLinkMeSpFrames.size(); i++)
	{
		if (mLinkMeSpFrames[i])
		{
			mLinkMeSpFrames[i]->mIsLinkFrameChanged = true;
		}
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::UpdateWorldData(double applicationTime, double elapsedTime)
{	
	if (mLinkFrame0 && mLinkFrame1 && mIsLinkFrameChanged)
	{
		UIFrame *parent = DynamicCast<UIFrame>(GetParent());

		float spSize = PX2_UISM.Size_Splitter;

		if (mIsHor)
		{
			float anchor0 = mLinkFrame0->GetAnchorHor()[0];
			const Float2 &paramHor0 = mLinkFrame0->GetAnchorParamHor();
			float anchor1 = mLinkFrame1->GetAnchorHor()[0];
			const Float2 &paramHor1 = mLinkFrame1->GetAnchorParamHor();

			float param0 = paramHor0[0];
			float param1 = -paramHor1[0];

			if (parent && !parent->IsHasChild(mLinkFrame0))
			{
				anchor0 = 0.0f;
				param0 = 0.0f;
			}

			if (parent && !parent->IsHasChild(mLinkFrame1))
			{
				anchor1 = 1.0f;
				param1 = 0.0f;
			}

			SetAnchorHor(anchor0, anchor1);

			if (parent && parent->IsHasChild(mLinkFrame0))
				param0 += spSize*(1.0f-mLinkFrame0->GetPvoit()[0]);

			if (parent && parent->IsHasChild(mLinkFrame1))
				param1 += spSize*mLinkFrame1->GetPvoit()[0];

			SetAnchorParamHor(param0, param1);
		}
		else
		{
			float anchor0 = mLinkFrame0->GetAnchorVer()[0];
			const Float2 &paramVer0 = mLinkFrame0->GetAnchorParamVer();
			float anchor1 = mLinkFrame1->GetAnchorVer()[0];
			const Float2 &paramVer1 = mLinkFrame1->GetAnchorParamVer();

			float param0 = paramVer0[0];
			float param1 = -paramVer1[0];

			if (parent && !parent->IsHasChild(mLinkFrame0))
			{
				anchor0 = 0.0f;
				param0 = 0.0f;
			}

			if (parent && !parent->IsHasChild(mLinkFrame1))
			{
				anchor1 = 1.0f;
				param1 = 0.0f;
			}

			SetAnchorVer(anchor0, anchor1);
			
			if (parent && parent->IsHasChild(mLinkFrame0))
				param0 += spSize*(1.0f-mLinkFrame0->GetPvoit()[1]);

			if (parent && parent->IsHasChild(mLinkFrame1))
				param1 += spSize*mLinkFrame1->GetPvoit()[1];

			SetAnchorParamVer(param0, param1);
		}

		mIsLinkFrameChanged = false;
	}

	UIFrame::UpdateWorldData(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------
void UISplitterFrame::OnNotPicked(int info)
{
	//if (mIsDraging)
	//{
	//	if (UIPT_PRESSED == info || UIPT_RELEASED==info)
	//	{
	//		SetDraging(false);
	//	}
	//}
}
//----------------------------------------------------------------------------
void UISplitterFrame::OnUIPicked(int info, Movable *child)
{
	if (!IsEnable()) return;

	UIFrame::OnUIPicked(info, child);

	if (UIPT_PRESSED == info)
	{
		if (mIsDragable)
			SetDraging(true);
	}
	else if (UIPT_RELEASED == info)
	{
		if (mIsDragable)
			SetDraging(false);
	}
	else if (UIPT_MOVED == info)
	{
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::DoExecute(Event *event)
{
	if (InputEventSpace::IsEqual(event, InputEventSpace::MouseMoved) ||
		InputEventSpace::IsEqual(event, InputEventSpace::TouchMoved))
	{
		if (mIsDragable && mIsDraging)
		{
			float sizeSP = PX2_UISM.Size_Splitter;

			UIFrame *parent = DynamicCast<UIFrame>(GetParent());
			Sizef parSize = parent->GetSize();

			Movable *mov = GetFirstParentDerivedFromType(UICanvas::TYPE);
			UICanvas *uiCanvas = DynamicCast<UICanvas>(mov);
			if (uiCanvas)
			{
				int viewID = uiCanvas->GetViewID();
				InputEventListener *iel = PX2_INPUTMAN.GetInputListener(viewID);
				if (iel)
				{
					InputEventData &ied = iel->mCurInputEventData;

					APoint origin;
					AVector direction;
					if (uiCanvas->GetPickRay(ied.MTPos.X(), ied.MTPos.Z(),
						origin, direction))
					{
						Transform inverTrans = parent->WorldTransform.InverseTransform();
						APoint localPos = inverTrans * origin;

						if (mIsHor)
						{
							float framePosOrigin = parent->LeftBottomCornerOffset.Z() + parSize.Height * GetAnchorVer()[0];
							float paramZ = localPos.Z() - framePosOrigin;

							float beforeParamVer = GetAnchorParamVer()[0];
							SetAnchorParamVer(Float2(paramZ, 0.0f));

							UpdateWorldData(Time::GetTimeInSeconds(), 0.0);
							bool isCanMake = _IsCanMakeBlcokFramesChange();
							if (isCanMake)
							{
								_MarkLinkMeFramesChange();
								_MarkBlockFramesChange();
							}
							else
							{
								SetAnchorParamVer(Float2(beforeParamVer, 0.0f));
							}
						}
						else
						{
							float framePosOrigin = parent->LeftBottomCornerOffset.X() + parSize.Width * GetAnchorHor()[0];
							float paramX = localPos.X() - framePosOrigin;

							float beforeParamHor = GetAnchorParamHor()[0];
							SetAnchorParamHor(Float2(paramX, 0.0f));

							UpdateWorldData(Time::GetTimeInSeconds(), 0.0);
							bool isCanMake = _IsCanMakeBlcokFramesChange();
							if (isCanMake)
							{
								_MarkLinkMeFramesChange();
								_MarkBlockFramesChange();
							}
							else
							{
								SetAnchorParamHor(Float2(beforeParamHor, 0.0f));
							}
						}
					}
				}
			}
		}
	}
	else if (InputEventSpace::IsEqual(event, InputEventSpace::MouseReleased))
	{
		if (IsDraging())
		{
			SetDraging(false);
		}
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::SetDragable(bool isDragable)
{
	mIsDragable = isDragable;
}
//----------------------------------------------------------------------------
void UISplitterFrame::SetDraging(bool isDraged)
{
	mIsDraging = isDraged;

	if (mIsDraging)
	{
		SetColor(PX2_UISM.Color_Splitter_Draging);
	}
	else
	{
		SetColor(PX2_UISM.Color_Splitter);
	}
}
//----------------------------------------------------------------------------
void UISplitterFrame::_AddAuiBlockFrame(UIAuiBlockFrame *blockframe)
{
	if (!blockframe)
		return;

	for (int i=0; i<(int)mAuiBlockFrames.size(); i++)
	{
		if (blockframe == mAuiBlockFrames[i])
			return;
	}

	mAuiBlockFrames.push_back(blockframe);
}
//----------------------------------------------------------------------------
void UISplitterFrame::_RemoveAuiBlockFrame(UIAuiBlockFrame *blockframe)
{
	if (!blockframe)
		return;

	std::vector<UIAuiBlockFrame*>::iterator it = mAuiBlockFrames.begin();
	for(; it!=mAuiBlockFrames.end(); it++)
	{
		if (blockframe == *it)
		{
			mAuiBlockFrames.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
bool UISplitterFrame::_IsCanMakeBlcokFramesChange()
{
	for (int i = 0; i < (int)mAuiBlockFrames.size(); i++)
	{
		const Sizef &minSize = mAuiBlockFrames[i]->GetMinSize();
		if (!minSize.IsEmpty())
		{
			Sizef outSize;
			APoint outPos;
			UIAuiBlockFrame::_UpdateLayout(mAuiBlockFrames[i], false,
				&outSize, &outPos);

			if (outSize.Width < minSize.Width ||
				outSize.Height < minSize.Height)
			{
				return false;
			}
		}
	}

	return true;
}
//----------------------------------------------------------------------------
void UISplitterFrame::_MarkBlockFramesChange()
{
	for (int i=0; i<(int)mAuiBlockFrames.size(); i++)
	{
		mAuiBlockFrames[i]->_MarkRelatvieChange();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �־û�֧��
//----------------------------------------------------------------------------
UISplitterFrame::UISplitterFrame(LoadConstructor value) :
UIFrame(value),
mIsHor(true),
mLinkFrame0(0),
mLinkFrame1(0),
mIsLinkFrameChanged(true),
mIsDragable(true),
mIsDraging(false)
{
}
//----------------------------------------------------------------------------
void UISplitterFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UISplitterFrame, source);
}
//----------------------------------------------------------------------------
void UISplitterFrame::Link(InStream& source)
{
	UIFrame::Link(source);

	if (mIPTCtrl)
		source.ResolveLink(mIPTCtrl);
}
//----------------------------------------------------------------------------
void UISplitterFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UISplitterFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UISplitterFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UISplitterFrame, target);
}
//----------------------------------------------------------------------------
int UISplitterFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------