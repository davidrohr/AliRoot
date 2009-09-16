// @(#) $Id: AliHLTTPCCAStartHitsFinder.cxx 27042 2008-07-02 12:06:02Z richterm $
// **************************************************************************
// This file is property of and copyright by the ALICE HLT Project          *
// ALICE Experiment at CERN, All rights reserved.                           *
//                                                                          *
// Primary Authors: David Rohr <drohr@kip.uni-heidelberg.de>				*
//                  for The ALICE HLT Project.                              *
//                                                                          *
// Permission to use, copy, modify and distribute this software and its     *
// documentation strictly for non-commercial purposes is hereby granted     *
// without fee, provided that the above copyright notice appears in all     *
// copies and that both the copyright notice and this permission notice     *
// appear in the supporting documentation. The authors make no claims       *
// about the suitability of this software for any purpose. It is            *
// provided "as is" without express or implied warranty.                    *
//                                                                          *
//***************************************************************************

#include "AliHLTTPCCAStartHitsSorter.h"
#include "AliHLTTPCCATracker.h"

GPUd() void AliHLTTPCCAStartHitsSorter::Thread
( int nBlocks, int nThreads, int iBlock, int iThread, int iSync,
  AliHLTTPCCASharedMemory &s, AliHLTTPCCATracker &tracker )
{
  if ( iSync == 0 ) {
    if ( iThread == 0 ) {
		const int GPUFixedBlockCount = tracker.GPUParametersConst()->fGPUFixedBlockCount;
	  const int tmpNRows = tracker.Param().NRows() - 6;
	  int nRows = iBlock == 29 ? (tmpNRows - (tmpNRows / 30) * 29) : (tmpNRows / 30);
	  int nStartRow = (tmpNRows / 30) * iBlock + 1;
      int StartOffset = 0;
	  int StartOffset2 = 0;
	  int LastBlockEndTracklet = 0;
	  int nCurrentBlock = 0;

      for (int ir = 1;ir < tracker.Param().NRows() - 5;ir++)
	  {
	    if (ir < nStartRow)
			StartOffset2 += tracker.RowStartHitCountOffset()[ir].x;

		if (iBlock == nBlocks - 1 && nCurrentBlock < GPUFixedBlockCount)
		{
			StartOffset += tracker.RowStartHitCountOffset()[ir].x;
			for (int i = LastBlockEndTracklet + HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS;i <= StartOffset;i += HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS)
			{
				if (LastBlockEndTracklet / (HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS) != i / (HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS))
				{
					tracker.BlockStartingTracklet()[nCurrentBlock].x = LastBlockEndTracklet;
					tracker.BlockStartingTracklet()[nCurrentBlock++].y = HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS;
					LastBlockEndTracklet += HLTCA_GPU_THREAD_COUNT - HLTCA_GPU_TRACKLET_CONSTRUCTOR_NMEMTHREDS;
					if (nCurrentBlock == GPUFixedBlockCount)
					{
						break;
					}
				}
			}
			if ((ir + 1) % HLTCA_GPU_SCHED_ROW_STEP == 0 && nCurrentBlock < GPUFixedBlockCount)
			{
				if (LastBlockEndTracklet != StartOffset)
				{
					tracker.BlockStartingTracklet()[nCurrentBlock].x = LastBlockEndTracklet;
					tracker.BlockStartingTracklet()[nCurrentBlock++].y = StartOffset - LastBlockEndTracklet;
					LastBlockEndTracklet = StartOffset;
				}
			}
			if (nCurrentBlock == GPUFixedBlockCount)
			{
				tracker.GPUParameters()->fScheduleFirstDynamicTracklet = LastBlockEndTracklet;
			}
		}
	  }
	  if (iBlock == nBlocks - 1)
	  {
	    if (nCurrentBlock < GPUFixedBlockCount)
		{
			tracker.BlockStartingTracklet()[nCurrentBlock].x = LastBlockEndTracklet;
			tracker.BlockStartingTracklet()[nCurrentBlock++].y = StartOffset - LastBlockEndTracklet;
			tracker.GPUParameters()->fScheduleFirstDynamicTracklet = StartOffset;
		}
		for (int i = nCurrentBlock;i < HLTCA_GPU_BLOCK_COUNT;i++)
		{
			tracker.BlockStartingTracklet()[i].x = 0;
			tracker.BlockStartingTracklet()[i].y = 0;			
		}
	  }
	  s.fStartOffset = StartOffset2;
	  s.fNRows = nRows;
      s.fStartRow = nStartRow;
    }
  } else if ( iSync == 1 ) {
	int StartOffset = s.fStartOffset;
    for (int ir = 0;ir < s.fNRows;ir++)
	{
		AliHLTTPCCAHitId *const startHits = tracker.TrackletStartHits();
		AliHLTTPCCAHitId *const tmpStartHits = tracker.TrackletTmpStartHits();
		const int tmpLen = tracker.RowStartHitCountOffset()[ir + s.fStartRow].x;			//Length of hits in row stored by StartHitsFinder
		const int tmpOffset = tracker.RowStartHitCountOffset()[ir + s.fStartRow].y;			//Offset of first hit in row of unsorted array by StartHitsFinder
		if (iThread == 0)
			tracker.RowStartHitCountOffset()[ir + s.fStartRow].z = StartOffset;				//Store New Offset Value of sorted array

		for (int j = iThread;j < tmpLen;j += nThreads)
		{
			startHits[StartOffset + j] = tmpStartHits[tmpOffset + j];
		}
		StartOffset += tmpLen;
    }
  }
}

