// experience.component.ts
import { AfterViewInit, Component } from '@angular/core';
import { Router, RouterLink, RouterLinkActive } from '@angular/router';
import { ScrollService } from '../../services/scroll.service';
import { ViewportScroller } from '@angular/common';

@Component({
  selector: 'app-experience',
  standalone: true,
  imports: [RouterLink, RouterLinkActive],
  templateUrl: './experience.component.html',
  styleUrl: './experience.component.css',
})
export class ExperienceComponent implements AfterViewInit {
  constructor(
    private scrollService: ScrollService,
    private router: Router,
    private viewportScroller: ViewportScroller
  ) {}

  ngAfterViewInit() {
    this.scrollService.scrollObservable.subscribe((section) => {
      setTimeout(() => {
        this.scrollToElement(section);
      }, 0);
    });
  }

  scrollToElement(section: string) {
    const element = document.getElementById(section);
    if (element) {
      this.viewportScroller.scrollToAnchor(element.id);
    }
  }

  noClickReadMore(section: string, navigateTo: string) {
    this.scrollService.scrollTo(section);
    this.router.navigate([navigateTo]);
  }
}
